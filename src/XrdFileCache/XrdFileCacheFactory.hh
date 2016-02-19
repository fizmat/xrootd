#ifndef __XRDFILECACHE_FACTORY_HH__
#define __XRDFILECACHE_FACTORY_HH__
//----------------------------------------------------------------------------------
// Copyright (c) 2014 by Board of Trustees of the Leland Stanford, Jr., University
// Author: Alja Mrak-Tadel, Matevz Tadel, Brian Bockelman
//----------------------------------------------------------------------------------
// XRootD is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// XRootD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with XRootD.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------------

#include <string>
#include <vector>
#include <map>

#include "XrdSys/XrdSysPthread.hh"
#include "XrdOuc/XrdOucCache.hh"

#include "XrdCl/XrdClDefaultEnv.hh"
#include "XrdVersion.hh"
#include "XrdFileCacheDecision.hh"

class XrdOucStream;
class XrdSysError;

namespace XrdCl
{
   class Log;
}

namespace XrdFileCache {
   class Cache;
}

namespace XrdFileCache
{
   //----------------------------------------------------------------------------
   //! Contains parameters configurable from the xrootd config file.
   //----------------------------------------------------------------------------
   struct Configuration
   {
      Configuration() :
         m_hdfsmode(false),
         m_diskUsageLWM(-1),
         m_diskUsageHWM(-1),
         m_bufferSize(1024*1024),
	 m_NRamBuffers(8000),
         m_prefetch(false),
         m_prefetch_max_blocks(10),
         m_hdfsbsize(128*1024*1024) {}

      bool m_hdfsmode;      //!< flag for enabling block-level operation
      std::string m_cache_dir;        //!< path of disk cache
      std::string m_username;         //!< username passed to oss plugin

      long long m_diskUsageLWM;       //!< cache purge low water mark
      long long m_diskUsageHWM;       //!< cache purge high water mark

      long long m_bufferSize;         //!< prefetch buffer size, default 1MB
      int       m_NRamBuffers;        //!< number of total in-memory cache blocks
      bool      m_prefetch;           //!< prefetch enable state        
      size_t    m_prefetch_max_blocks;//!< maximum number of blocks to prefetch per file

      long long m_hdfsbsize;          //!< used with m_hdfsmode, default 128MB
   };


   //----------------------------------------------------------------------------
   //! Instantiates Cache and Decision plugins. Parses configuration file.
   //----------------------------------------------------------------------------
   class Factory : public XrdOucCache
   {
      public:
         //--------------------------------------------------------------------------
         //! Constructor
         //--------------------------------------------------------------------------
         Factory();

         //---------------------------------------------------------------------
         //! \brief Unused abstract method. This method is implemented in the
         //! the Cache class.
         //---------------------------------------------------------------------
         virtual XrdOucCacheIO *Attach(XrdOucCacheIO *, int Options=0) { return NULL; }

         //---------------------------------------------------------------------
         //! \brief Unused abstract method. This information is available in
         //! the Cache class.
         //---------------------------------------------------------------------
         virtual int isAttached() { return false; }

         //---------------------------------------------------------------------
         //! Creates XrdFileCache::Cache object
         //---------------------------------------------------------------------
         virtual XrdOucCache* Create(Parms &, XrdOucCacheIO::aprParms *aprP);

         XrdOss* GetOss() const { return m_output_fs; }

         //---------------------------------------------------------------------
         //! Getter for xrootd logger
         //---------------------------------------------------------------------
          XrdSysError& GetSysError() { return m_log; }

         //--------------------------------------------------------------------
         //! \brief Makes decision if the original XrdOucCacheIO should be cached.
         //!
         //! @param & URL of file
         //!
         //! @return decision if IO object will be cached.
         //--------------------------------------------------------------------
         bool Decide(XrdOucCacheIO*);

         //------------------------------------------------------------------------
         //! Reference XrdFileCache configuration
         //------------------------------------------------------------------------
         const Configuration& RefConfiguration() const { return m_configuration; }


         //---------------------------------------------------------------------
         //! \brief Parse configuration file
         //!
         //! @param logger             xrootd logger
         //! @param config_filename    path to configuration file
         //! @param parameters         optional parameters to be passed
         //!
         //! @return parse status
         //---------------------------------------------------------------------
         bool Config(XrdSysLogger *logger, const char *config_filename, const char *parameters);

         //---------------------------------------------------------------------
         //! Singleton access.
         //---------------------------------------------------------------------
         static Factory &GetInstance();

         //---------------------------------------------------------------------
         //! Version check.
         //---------------------------------------------------------------------
         static bool VCheck(XrdVersionInfo &urVersion) { return true; }

         //---------------------------------------------------------------------
         //! Thread function running disk cache purge periodically.
         //---------------------------------------------------------------------
         void CacheDirCleanup();


         Cache* GetCache() { return m_cache; }
      private:
         bool ConfigParameters(std::string, XrdOucStream&);
         bool ConfigXeq(char *, XrdOucStream &);
         bool xdlib(XrdOucStream &);

         XrdCl::Log* clLog() const { return XrdCl::DefaultEnv::GetLog(); }

         static Factory   *m_factory;   //!< this object

         XrdSysError       m_log;       //!< XrdFileCache namespace logger
         XrdOucCacheStats  m_stats;     //!< passed to cache, currently not used
         XrdOss           *m_output_fs; //!< disk cache file system

         std::vector<XrdFileCache::Decision*> m_decisionpoints; //!< decision plugins

         std::map<std::string, long long> m_filesInQueue;

         Configuration     m_configuration; //!< configurable parameters

         Cache*            m_cache;
   };
}

#endif
