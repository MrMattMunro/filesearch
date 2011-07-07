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

import java.sql.Connection;
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
	public boolean createSearchertable(String namespace) throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.createSearchertable(namespace);
	}
	
	/**
	 * 取出待删除索引的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedDelSeacher(Connection conn)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedDelSeacher(conn);
	}

	/**
	 * 取出待建立索引的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedIndexSeacher(Connection conn)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedIndexSeacher(conn);
	}
	
	/**
	 * 取出需要更新的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedUpdateSeacher(Connection conn)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.getNeedUpdateSeacher(conn);
	}

	/**
	 * 删除搜索对象
	 * 
	 * @param id 搜索对象Id
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean deleteSeacherById(String id)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.deleteSearcher(id);
	}
	
	/**
	 * 更新搜索对象
	 * 
	 * @param conn 数据库连接
	 * @param bean 搜索对象
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean updateSearcher(Connection conn,SearcherBean bean)
			throws DBException, LogicException {
		SearcherDao searcherDao = new SearcherDao();
		return searcherDao.updateSearcherById(conn, bean);
	}
	
}
