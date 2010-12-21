package com.searchlocal.service;

import com.searchlocal.dao.BaseDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;

public class BaseService {

	public boolean createDataBase(String namespace) throws DBException,
			LogicException {
		return BaseDao.createDataBase(namespace);
	}

	public boolean dropDataBase(String namespace) throws DBException,
			LogicException {
		return BaseDao.dropDataBase(namespace);
	}

	public boolean createFileTable(String namespace) throws DBException,
			LogicException {
		return BaseDao.dropDataBase(namespace);
	}

}
