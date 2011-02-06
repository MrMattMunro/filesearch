/**
 * $RCSfile: FileOpenerService.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import java.util.List;

import com.searchlocal.bean.FileOpenerBean;
import com.searchlocal.dao.FileOpenerDao;
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
public class FileOpenerService {

	/**
	 * 创建文件打开表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createFileOpenertable(String namespace) throws DBException, LogicException {
		FileOpenerDao fileOpenerDao = new FileOpenerDao();
		return fileOpenerDao.createFileOpenertable(namespace);
	}

	/**
	 * 取出文件打开软件记录
	 * 
	 * @return list FileOpener记录列表
	 * @throws LogicException
	 * @throws DBException 
	 */
	public List<FileOpenerBean> getFileOpener(String namespace) throws LogicException, DBException {
		FileOpenerDao fileOpenerDao = new FileOpenerDao();
		return fileOpenerDao.getFileOpener(namespace);
	}

	/**
	 * 插入FileOpener记录
	 * 
	 * @param beanList FileOpener数据
	 * @param namespace 数据库 
	 * @throws DBException 
	 * @throws LogicException 
	 */
	public boolean insertFileOpenRecord(List<FileOpenerBean> beanList, String namespace)
			throws LogicException, DBException {
		FileOpenerDao fileOpenerDao = new FileOpenerDao();
		return fileOpenerDao.insertFileOpenRecord(beanList, namespace);
	}
	
	/**
	 * 根据文件类型来取得打开文件
	 * 
	 * @param namespace 数据库 
	 * @param fileType 文件类型
	 * @throws DBException 
	 * @throws LogicException 
	 */
	public  List<FileOpenerBean> getFileOpenerByFileType(String namespace, String fileType)
			throws LogicException, DBException {
		FileOpenerDao fileOpenerDao = new FileOpenerDao();
		return fileOpenerDao.getFileOpenerByFileType(namespace, fileType);
	}
}
