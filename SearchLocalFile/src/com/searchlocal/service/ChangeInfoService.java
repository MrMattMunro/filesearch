/**
 * $RCSfile: SearcherDao.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import java.util.ArrayList;
import java.util.List;

import com.searchlocal.bean.ChangInfoBean;
import com.searchlocal.dao.ChangeInfoDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;

/**
 * 变化文件服务类
 * 
 * <p>Title: 变化文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChangeInfoService {

	/**
	 * 创建变化文件表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createChangeInfoTable(String namespace) throws DBException, LogicException {
		ChangeInfoDao changeInfoDao = new ChangeInfoDao();
		return changeInfoDao.createChangeInfotable(namespace);
    }
	
	/**
	 * 根据操作标记来取得变化文件记录
	 * 
	 * @param namespace 数据库名
	 * @param operflg 操作标记
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<ChangInfoBean> getChangeInfoByHasoper(String namespace, String operflg) throws DBException, LogicException {
		ChangeInfoDao changeInfoDao = new ChangeInfoDao();
		return changeInfoDao.getChangeInfoByHasoper(namespace, operflg);
    }
	
	/**
	 * 更新变化文件记录
	 * 
	 * @param beanList 变化文件记录列表
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean updateChangeInfo(List<ChangInfoBean> beanList, String namespace) throws DBException, LogicException {
		ChangeInfoDao changeInfoDao = new ChangeInfoDao();
		return changeInfoDao.updateChangeInfo(beanList, namespace);
    }
	
	/**
	 * 更新变化文件记录
	 * 
	 * @param bean 变化文件记录
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean updateHasOper(ChangInfoBean bean, String namespace) throws DBException, LogicException {
		ChangeInfoDao changeInfoDao = new ChangeInfoDao();
		List<ChangInfoBean> beanList = new ArrayList<ChangInfoBean>();
		beanList.add(bean);
		return changeInfoDao.updateChangeInfo(beanList, namespace);
    }

}
