/**
 * $RCSfile: SeacherService.java
 * $Revision: 1.0
 * $Date: Feb 1, 2011
 *
 * Copyright (C) 2010 ICSS, Inc. All rights reserved.
 *
 * This software is the proprietary information of ICSS, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import java.util.List;

import com.searchlocal.bean.SearcherBean;
import com.searchlocal.dao.SearcherDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;

/**
 * 搜索对象服务类
 * 
 * <p>Title: Pdf文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SeacherService {

	/**
	 * 创建搜索对象表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createResulttable(String namespace) throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.createSearchertable(namespace);
	}

	/**
	 * 取出待删除索引的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedDelSeacher(String namespace)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedDelSeacher(namespace);
	}

	/**
	 * 取出待建立索引的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedIndexSeacher(String namespace)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedIndexSeacher(namespace);
	}
	
	/**
	 * 取出需要更新的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedUpdateSeacher(String namespace)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedUpdateSeacher(namespace);
	}
}
