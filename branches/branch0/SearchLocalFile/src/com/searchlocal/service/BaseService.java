/**
 * $RCSfile: BaseService.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import com.searchlocal.dao.BaseDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;

/**
 * 服务类基类
 * 
 * <p>Title: 服务类基类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class BaseService {

	/**
	 * 创建数据库
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createDataBase(String namespace) throws DBException, LogicException {
		return BaseDao.createDataBase(namespace);
	}

	/**
	 * 删除数据库
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean dropDataBase(String namespace) throws DBException, LogicException {
		return BaseDao.dropDataBase(namespace);
	}

}
