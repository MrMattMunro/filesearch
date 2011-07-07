/**
 * $RCSfile: PptService.java
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

import com.searchlocal.bean.PptFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.PptDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.PptReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Ppt文件服务类
 * 
 * <p>Title: Pdf文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class PptService {

	/**
	 * 对Pdf文件建立索引
	 * 
	 * @param pptbean Ppt文件Bean
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(PptFileBean pptbean, String namespace)
			throws DBException, LogicException {
		List<PptFileBean> fileBeanList;
		PptReader reader = new PptReader();
		fileBeanList = reader.getPptFile(pptbean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.PPT, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Ppt表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createPptTable(String namespace) throws LogicException, DBException {
		PptDao PptDao;
		PptDao = new PptDao();
		return PptDao.createPpttable(namespace);
	}
}
