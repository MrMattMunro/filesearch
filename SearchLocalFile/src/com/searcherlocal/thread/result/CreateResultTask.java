/**
 * $RCSfile: CreateResultTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searcherlocal.thread.result;

import java.io.File;
import java.sql.Connection;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.ResultBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.BaseDao;
import com.searchlocal.lucene.ContentSearcher;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.SearchParam;
import com.searchlocal.service.ResultService;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.util.KeyWordUtil;
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
public class CreateResultTask extends CRunnable {
	
	/** DB连接 */
	private static Connection conn = null;

	/** 
	 * 执行
	 */
	public void excute() {
		// 关键字文件
		String keyWordPath = Constant.path + "com\\searchlocal\\properties\\keyWord.properties";
		File keyWordFile = new File(keyWordPath);
		// 关键字文件存在的时候,才进行检索索引文件
		if(keyWordFile.exists()){
			// 查找结果集服务类
			ResultService resultService = new ResultService();
			// 取得数据库连接
			try {
				if(null == conn){
					conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);	
				}
				// 关键字和id
				String keyWord = KeyWordUtil.getMsgbyId("keyword");
				String id = KeyWordUtil.getMsgbyId("id");
				// 搜索名
				String database = Constant.CommonInfo.SEARCHER + id;
				// 删除XML节点
				XMLConfig xmler = new XMLConfig();
				List<CreateNewParam> entityList = xmler.getEntityList();
				// 生成SearchParam
				SearchParam searchParam = new SearchParam();
				for (Iterator<CreateNewParam> iter = entityList.iterator(); iter.hasNext();) {
					CreateNewParam element = (CreateNewParam) iter.next();
					String searchName = element.getSearchname();
					if(searchName.equals(database)){
						searchParam.setIndexPath(element.getIndexpath());
						searchParam.setKeyWord(keyWord);
					}
				}
				// 检索索引文件,取得结果集列表
				searchParam.setStartRow(0);
				searchParam.setEndRow(15);
				List<ResultBean> resultList = ContentSearcher.query(searchParam);
				// 先删除后插入数据
				resultService.deleteResultRecord(conn, Constant.CommonInfo.DATABASE);
				resultService.insertResultRecord(conn, resultList, Constant.CommonInfo.DATABASE);
				resultList.clear();
				// 删除关键字文件
				entityList.clear();
				KeyWordUtil.prop.clear();
				keyWordFile.delete();
				System.gc();
			} catch (Exception e) {
				e.printStackTrace();
			}
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
				System.out.println("监控检索开始");
				sleep(1 * 500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
