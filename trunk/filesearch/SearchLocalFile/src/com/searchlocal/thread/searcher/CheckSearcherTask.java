/**
 * $RCSfile: CheckSearcherTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.searcher;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.SearcherBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.BaseDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.exhander.ExceptionHandler;
import com.searchlocal.menu.MessageFrame;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.UpdateParam;
import com.searchlocal.service.BaseService;
import com.searchlocal.service.ChangeInfoService;
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.FileService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.SeacherService;
import com.searchlocal.service.TxtService;
import com.searchlocal.service.WordService;
import com.searchlocal.thread.CheckThreadPoolTask;
import com.searchlocal.thread.SearchFile;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.update.CheckUpdateThreadPoolTask;
import com.searchlocal.thread.update.UpdateFile;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.WinMsgUtil;
import com.searchlocal.util.XMLConfig;

/**
 * 监控搜索对象线程
 * 
 * <p>Title: 监控搜索对象线程</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CheckSearcherTask extends CRunnable {
	
	/** DB连接 */
	private static Connection conn = null;

	/** 消息 */
	private static MenuMessageUtil msg = new MenuMessageUtil();

	public void excute() {
		// 取得连接
		try {
			if(null == conn){
				conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);	
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		SeacherService searcherService = new SeacherService();
		try {
			// 取得待处理的搜索对象
			List<SearcherBean> needDelList = searcherService.getNeedDelSeacher(conn);
			List<SearcherBean> needIdxList = searcherService.getNeedIndexSeacher(conn);
			List<SearcherBean> needUpdList = searcherService.getNeedUpdateSeacher(conn);

			// 存在需删除的搜索对象
			if (0 < needDelList.size()) {
				// 改变图标显示信息
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_DELETINGINDEX);
				// 删除DB
				BaseService baseService = new BaseService();
				for (Iterator<SearcherBean> neddDel = needDelList.iterator(); neddDel.hasNext();) {
					SearcherBean searcherBean = (SearcherBean) neddDel.next();
					String id = searcherBean.getId();
					String database = Constant.CommonInfo.SEARCHER + id;
					try {
						baseService.dropDataBase(database);
					} catch (DBException e1) {
						String errormsg = msg.getMsgbyId(Constant.info_deletedindex);
						MessageFrame.showmessage(errormsg);
					} catch (LogicException e1) {
						String errormsg = msg.getMsgbyId(Constant.info_deletedindex);
						MessageFrame.showmessage(errormsg);
					}
					// 删除索引目录
					FileUtil.delFolder(searcherBean.getIndexPath(), true);

					// 删除XML节点
					XMLConfig xmler = new XMLConfig();
					xmler.removeXML(database);
					// 删除Id
					searcherService.deleteSeacherById(id);
					// 改变图标显示信息：结束
					SearchlocalApp.completeWork();

				}
				// 显示删除索引完成
				String message = msg.getMsgbyId(Constant.info_deletedindex);
				MessageFrame.showmessage(message);
				// 重启程序
				String slfilepath = ConstantExeFileUtil.getOpenerbyId("slfile");
				CourseUtil.restart(slfilepath);
			}

			// 存在需建立索引的搜索对象
			if (0 < needIdxList.size()) {
				// 改变图标显示信息
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_CREATINGINDEX);
				for (Iterator<SearcherBean> needIdx = needIdxList.iterator(); needIdx.hasNext();) {
					SearcherBean searcherBean = (SearcherBean) needIdx.next();
					String id = searcherBean.getId();
					String database = Constant.CommonInfo.SEARCHER + id;
					String indexpath = searcherBean.getIndexPath();
					String path = searcherBean.getPath();
					String filetype = searcherBean.getFileType();

					// XML操作对象
					XMLConfig xmler = new XMLConfig();
					// 建立DB表
					BaseService baseService = new BaseService();
					FileService fileService = new FileService();
					ChangeInfoService changeInfoService = new ChangeInfoService();
					try {
						baseService.createDataBase(database);
						fileService.createFileTable(database);
						changeInfoService.createChangeInfoTable(database);
					} catch (DBException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					} catch (LogicException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					}
					// 写入XML
					CreateNewParam newparam = new CreateNewParam();
					newparam.setSearchname(database);
					newparam.setPath(path);
					newparam.setIndexpath(indexpath);
					newparam.setSelectfiletype(Arrays.asList(filetype.split(",")));
					xmler.writeXML(newparam);

					// 开始搜索文件
					SearchFile searchFile = new SearchFile();
					searchFile.listen(newparam);
					while (true) {
						ThreadUtil.sleep(2000);
						if (CheckThreadPoolTask.isIsdone()) {
							// 显示建立索引完成
							String message = msg.getMsgbyId(Constant.info_completeindex);
							MessageFrame.showmessage(message);
							// 改变图标显示信息：结束
							SearchlocalApp.completeWork();
							// 改变T_Searcher表的状态
							// 更新成已建成索引
							searcherBean.setHasCreateIndex(Constant.HasCreateIndexFlg.HAS_CREAT_INDEX);
							searcherBean.setHasUpdate(Constant.HasUpdateFlg.HAS_UPATE);
							searcherBean.setHasDel(Constant.HasDelFlg.HAS_NOT_DEL);
							searcherService.updateSearcher(conn, searcherBean);
							// 通知slFileSearch服务重新加载Searcher.xml文件
							// WinMsgUtil.notifyMsg();
							// 重启程序
							String slfile = ConstantExeFileUtil.getOpenerbyId("slfile");
							CourseUtil.restart(slfile);
							break;
						}
					}
				}
			}

			// 存在需更新的搜索对象
			if (0 < needUpdList.size()) {
				// 改变图标显示信息
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_UPDATINGINDEX);
				for (Iterator<SearcherBean> needUpd = needUpdList.iterator(); needUpd.hasNext();) {
					// 从DB中查找需要更新搜索对象
					SearcherBean searcherBean = (SearcherBean) needUpd.next();
					String id = searcherBean.getId();
					String database = Constant.CommonInfo.SEARCHER + id;
					String indexpath = searcherBean.getIndexPath();
					String path = searcherBean.getPath();
					String filetype = searcherBean.getFileType();

					// 从DB取出文档类型
					String[] filetypeArr = filetype.split(",");

					// XML操作对象
					XMLConfig xmler = new XMLConfig();
					List<String> oldFileType = new ArrayList<String>();
					List<CreateNewParam> parmList = xmler.getEntityList();
					for (Iterator<CreateNewParam> parmiter = parmList.iterator(); parmiter
							.hasNext();) {
						CreateNewParam param = (CreateNewParam) parmiter.next();
						String searchName = param.getSearchname();
						// 找到对应的搜索对象
						if (searchName.equals(database)) {
							oldFileType = param.getSelectfiletype();
						}
					}
					// 循环DB里面的文档类型
					// 需要增加
					List<String> addFiletype = new ArrayList<String>();
					for (int i = 0; i < filetypeArr.length; i++) {
						String tempfiletype = filetypeArr[i];
						// 判断是否需要增加
						if (!oldFileType.contains(tempfiletype)) {
							addFiletype.add(tempfiletype);
						}
					}

					// 需要删除场合
					List<String> tempFileTypeList = Arrays.asList(filetypeArr);
					List<String> delFiletype = new ArrayList<String>();
					// 循环XML文件中的文件类型
					for (Iterator<String> oldFileTypeItr = oldFileType.iterator(); oldFileTypeItr
							.hasNext();) {
						String tempfiletype = (String) oldFileTypeItr.next();
						// 判断是否需要删除
						if (!tempFileTypeList.contains(tempfiletype)) {
							delFiletype.add(tempfiletype);
						}
					}

					// 开始更新文件
					UpdateParam param = new UpdateParam();
					param.setSearchname(database);
					param.setPath(path);
					param.setIndexpath(indexpath);
					param.setNeedAddfiletypes(addFiletype);
					param.setNeedDelfiletypes(delFiletype);
					UpdateFile updateFile = new UpdateFile();
					updateFile.listen(param);

					// 更新XML
					xmler.removeXML(database);
					CreateNewParam newparam = new CreateNewParam();
					newparam.setSearchname(database);
					newparam.setPath(path);
					newparam.setIndexpath(indexpath);
					newparam.setSelectfiletype(Arrays.asList(filetype.split(",")));
					xmler.writeXML(newparam);

					// 开始搜索文件
					while (true) {
						ThreadUtil.sleep(2000);
						if (CheckUpdateThreadPoolTask.isIsdone()) {
							// 显示建立索引完成
							String message = msg.getMsgbyId(Constant.info_updatedindex);
							MessageFrame.showmessage(message);
							// 改变图标显示信息：结束
							SearchlocalApp.completeWork();
							// 更新成已建成索引
							searcherBean.setHasUpdate(Constant.HasUpdateFlg.HAS_UPATE);
							searcherBean.setHasCreateIndex(Constant.HasCreateIndexFlg.HAS_CREAT_INDEX);
							searcherBean.setHasDel(Constant.HasDelFlg.HAS_NOT_DEL);
							searcherService.updateSearcher(conn, searcherBean);
							// 通知slFileSearch服务重新加载Searcher.xml文件
							// WinMsgUtil.notifyMsg();
							// 重启程序
							String slfile = ConstantExeFileUtil.getOpenerbyId("slfile");
							CourseUtil.restart(slfile);
							break;
						}
					}
				}
			}

		} catch (DBException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} catch (LogicException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} finally {
//			if (conn != null) {
//				try {
//					//conn.close();
//				} catch (SQLException e) {
//					e.printStackTrace();
//				}
//			}
		}
	}

	/** 
	 */
	public void run() {
		while (true) {
			synchronized (this) {
				excute();
			}
			try {
				System.out.println("执行周期开始");
				sleep(1 * 500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
