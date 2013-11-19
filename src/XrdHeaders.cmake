
install(
  FILES
  ${CMAKE_BINARY_DIR}/src/XrdVersion.hh
  ${CMAKE_SOURCE_DIR}/src/XrdVersionPlugin.hh
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xrootd )

set( XROOTD_PUBLIC_HEADERS
  XProtocol/XProtocol.hh
  XProtocol/XPtypes.hh
  Xrd/XrdBuffer.hh
  Xrd/XrdJob.hh
  Xrd/XrdLink.hh
  Xrd/XrdLinkMatch.hh
  Xrd/XrdProtocol.hh
  Xrd/XrdScheduler.hh
  XrdAcc/XrdAccAuthorize.hh
  XrdAcc/XrdAccPrivs.hh
  XrdCks/XrdCks.hh
  XrdCks/XrdCksCalc.hh
  XrdCks/XrdCksData.hh
  XrdCks/XrdCksManager.hh
  XrdClient/XrdClient.hh
  XrdClient/XrdClientAbs.hh
  XrdClient/XrdClientAbsMonIntf.hh
  XrdClient/XrdClientAdmin.hh
  XrdClient/XrdClientConst.hh
  XrdClient/XrdClientEnv.hh
  XrdClient/XrdClientUnsolMsg.hh
  XrdClient/XrdClientUrlInfo.hh
  XrdClient/XrdClientUrlSet.hh
  XrdClient/XrdClientVector.hh
  XrdCms/XrdCmsClient.hh
  XrdNet/XrdNet.hh
  XrdNet/XrdNetCmsNotify.hh
  XrdNet/XrdNetConnect.hh
  XrdNet/XrdNetOpts.hh
  XrdNet/XrdNetSocket.hh
  XrdOss/XrdOss.hh
  XrdOss/XrdOssDefaultSS.hh
  XrdOuc/XrdOucCRC.hh
  XrdOuc/XrdOucCache.hh
  XrdOuc/XrdOucCallBack.hh
  XrdOuc/XrdOucChain.hh
  XrdOuc/XrdOucDLlist.hh
  XrdOuc/XrdOucEnv.hh
  XrdOuc/XrdOucErrInfo.hh
  XrdOuc/XrdOucHash.hh
  XrdOuc/XrdOucHash.icc
  XrdOuc/XrdOucLock.hh
  XrdOuc/XrdOucName2Name.hh
  XrdOuc/XrdOucRash.hh
  XrdOuc/XrdOucRash.icc
  XrdOuc/XrdOucStream.hh
  XrdOuc/XrdOucString.hh
  XrdOuc/XrdOucTList.hh
  XrdOuc/XrdOucTable.hh
  XrdOuc/XrdOucTokenizer.hh
  XrdOuc/XrdOucTrace.hh
  XrdOuc/XrdOucUtils.hh
  XrdOuc/XrdOuca2x.hh
  XrdOuc/XrdOucEnum.hh
  XrdPosix/XrdPosixCallBack.hh
  XrdPosix/XrdPosixExtern.hh
  XrdPosix/XrdPosixOsDep.hh
  XrdPosix/XrdPosixXrootd.hh
  XrdPosix/XrdPosixXrootdPath.hh
  XrdSec/XrdSecEntity.hh
  XrdSec/XrdSecInterface.hh
  XrdSfs/XrdSfsAio.hh
  XrdSfs/XrdSfsInterface.hh
  XrdSys/XrdSysAtomics.hh
  XrdSys/XrdSysDNS.hh
  XrdSys/XrdSysError.hh
  XrdSys/XrdSysHeaders.hh
  XrdSys/XrdSysLogger.hh
  XrdSys/XrdSysPlatform.hh
  XrdSys/XrdSysPlugin.hh
  XrdSys/XrdSysPthread.hh
  XrdSys/XrdSysSemWait.hh
  XrdSys/XrdSysTimer.hh
  XrdSys/XrdSysXSLock.hh
  XrdXrootd/XrdXrootdMonData.hh
)

set( XROOTD_PRIVATE_HEADERS
  Xrd/XrdPoll.hh
  XrdClient/XrdClientConn.hh
  XrdClient/XrdClientConnMgr.hh
  XrdClient/XrdClientDebug.hh
  XrdClient/XrdClientInputBuffer.hh
  XrdClient/XrdClientLogConnection.hh
  XrdClient/XrdClientMessage.hh
  XrdClient/XrdClientPhyConnection.hh
  XrdClient/XrdClientReadCache.hh
  XrdClient/XrdClientSock.hh
  XrdNet/XrdNetPeer.hh
  XrdNet/XrdNetBuffer.hh
  XrdOfs/XrdOfs.hh
  XrdOfs/XrdOfsEvr.hh
  XrdOfs/XrdOfsHandle.hh
  XrdOfs/XrdOfsTrace.hh
  XrdSys/XrdSysPriv.hh

  XrdOss/XrdOssApi.hh
  XrdOss/XrdOssConfig.hh
  XrdOss/XrdOssError.hh
  XrdOuc/XrdOucExport.hh
  XrdOuc/XrdOucPList.hh
)

install_headers(
  ${CMAKE_INSTALL_INCLUDEDIR}/xrootd
  "${XROOTD_PUBLIC_HEADERS}" )

install_headers(
  ${CMAKE_INSTALL_INCLUDEDIR}/xrootd/private
  "${XROOTD_PRIVATE_HEADERS}" )
