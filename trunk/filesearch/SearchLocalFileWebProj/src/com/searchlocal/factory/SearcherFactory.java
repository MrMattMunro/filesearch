/**
 * $RCSfile: SearcherFactory.java
 * $Revision: 1.0
 * $Date: May 7, 2011
 *
 * Copyright (C) 2010 ICSS, Inc. All rights reserved.
 *
 * This software is the proprietary information of ICSS, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.factory;

import java.sql.Connection;
import java.util.List;

import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.dao.BaseDao;
import com.web.searchlocal.param.CreateNewParam;
import com.web.searchlocal.service.SearchService;
import com.web.searchlocal.service.impl.SearchServiceImpl;
import com.web.searchlocal.util.RecentSearcherIndexPathUtil;
import com.web.searchlocal.util.WebMessageUtil;

/**
 * 搜索对象工厂
 * 
 * <p>Title: 搜索对象工厂</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearcherFactory {

	/** 搜索对象 */
	public static List<CreateNewParam> searcherList = null;
	
	/** 搜索对象 */
	private static WebMessageUtil msg = new WebMessageUtil();

	/** DB连接 */
	private static Connection conn = null;

	/**
	 * 取得搜索对象列表
	 * 
	 * @return 搜索对象列表
	 */
	public static List<CreateNewParam> getSearcher() {
		
		if (null == searcherList) {
			// 取得连接
			try {
				if (null == conn) {
					conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);
				}
				SearchService searcherservice = new SearchServiceImpl();
				searcherList = searcherservice.getAllSearcher(conn);
				addRecentSearcher();
			} catch (Exception e) {
				e.printStackTrace();
			}
			return searcherList;
		}
		return searcherList;
	}
	

	/**
	 * 重新从DB里取出Searcher
	 * 
	 * @return 搜索对象列表
	 */
	public static List<CreateNewParam> updateSearchers() {
		// 取得连接
		try {
			if (null == conn) {
				conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);
			}
			SearchService searcherservice = new SearchServiceImpl();
			searcherList = searcherservice.getAllSearcher(conn);
			addRecentSearcher();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return searcherList;
	}
	
	/**
	 * 
	 * 加入最近修改文档对象
	 * 
	 * @return 搜索对象列表
	 */
	public static void addRecentSearcher() {
		CreateNewParam recentChangeFile = new CreateNewParam();
		String indexpath = RecentSearcherIndexPathUtil.getIdexPath(Constant.RecentFileInfo.INDEX_PATH_KEY);
		recentChangeFile.setIdexpath(indexpath);
		recentChangeFile.setPath(msg.getMsgbyId(Constant.web_recentchangfile));
		recentChangeFile.setId(Constant.RecentFileInfo.Id);
		recentChangeFile.setSelectfiletype(Constant.FileNameClassify.getAllTypeList());
		searcherList.add(recentChangeFile);
	}
}
