/**
 * $RCSfile: PdfService.java
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

import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.PdfDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.PdfReader;
import com.searchlocal.lucene.IndexBeanList;

/**
 * Pdf文件服务类
 * 
 * <p>Title: Pdf文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class PdfService {

	/**
	 * 对Pdf文件建立索引
	 * 
	 * @param pdfbean Pdf文件Bean
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(PdfFileBean pdfbean, String namespace)
			throws DBException, LogicException {
		List<PdfFileBean> fileBeanList;
		PdfReader reader = new PdfReader();
		fileBeanList = reader.getPdfFile(pdfbean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.PDF, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Pdf表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createPdfTable(String namespace) throws LogicException, DBException {
		PdfDao PdfDao;
		PdfDao = new PdfDao();
		return PdfDao.createPdftable(namespace);
	}
}
