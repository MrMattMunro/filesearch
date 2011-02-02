/**
 * $RCSfile: ResultService.java
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

import com.searchlocal.bean.ResultBean;
import com.searchlocal.dao.ResultDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;

/**
 * 查找结果集服务类
 * 
 * <p>Title: Pdf文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ResultService {

	/**
	 * 创建结果集表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createResulttable(String namespace) throws DBException, LogicException {
		ResultDao resultDao = new ResultDao();
		return resultDao.createResulttable(namespace);
	}

	/**
	 * 插入结果集
	 * 
	 * @param beanList 结果集
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertResultRecord(List<ResultBean> beanList, String namespace)
			throws DBException, LogicException {
		ResultDao resultDao = new ResultDao();
		return resultDao.insertResultRecord(beanList, namespace);
	}

	/**
	 * 删除搜索结果记录
	 * 
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean deleteResultRecord(String namespace) throws DBException, LogicException {
		ResultDao resultDao = new ResultDao();
		return resultDao.deleteResultRecord(namespace);
	}
}
