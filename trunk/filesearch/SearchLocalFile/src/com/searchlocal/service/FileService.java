/**
 * $RCSfile: FileService.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.constants.Constant;
import com.searchlocal.dao.FileDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.FileParam;
import com.searchlocal.util.StringUtils;

/**
 * 文件服务类
 * 
 * <p>Title: 文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileService {

	/**
	 * 执行Batch命令,导入数据
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean execBatch(String namespace) throws DBException, LogicException {
		FileDao fileDao = new FileDao();
		String filepath = Constant.datapath + Constant.filedatapath + Constant.suffixname;
		filepath = filepath.substring(1);
		filepath = StringUtils.editFilePath(filepath);

		fileDao.execbatch(filepath, namespace);
		String existedpath = filepath.substring(1, filepath.length() - 1);
		File file = new File(existedpath);
		// 删除batch的数据文件
		if (file.exists()) {
			file.delete();
		}
		return true;
	}

	/**
	 * 创建Batch用的csv文件
	 * 
	 * @param filebeanList 文件对象列表
	 * @param namespace 数据库名
	 * @param fileClassify 文件区分
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createBatchFile(List<FileParam> filebeanList, String namespace, int fileClassify)
			throws DBException, LogicException {
		// 生成csv文件
		File wordfile = new File(Constant.datapath + Constant.filedatapath + fileClassify
				+ Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!wordfile.exists()) {
				wordfile.createNewFile();
			}
			out = new FileOutputStream(wordfile, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// 写入数据
		for (Iterator<FileParam> iter = filebeanList.iterator(); iter.hasNext();) {
			FileParam element = (FileParam) iter.next();
			String temp = "";
			String path = element.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(element.getLastModify());
			temp = temp + "," + element.getError();
			temp = temp + "\r\n";
			try {
				out.write(temp.getBytes("utf-8"));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		// 关闭流
		try {
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return filebeanList.size();
	}

	/**
	 * 创建Batch用的csv文件
	 * 
	 * @param beanList 文件对象列表
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertFileRecord(List<FileParam> beanList, String namespace) throws DBException,
			LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.insertFileRecord(beanList, namespace);
	}

	/**
	 * 更新Bean列表
	 * 
	 * @param beanList 文件对象列表
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean updateFileRecord(List<FileParam> beanList, String namespace) throws DBException,
			LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.updateFileRecord(beanList, namespace);
	}

	/**
	 * 根据搜索对象取得文件信息
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<FileParam> getFileRecordList(String namespace) throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		List<FileParam> fileRecord = fileDao.getFileRecord(namespace);
		return fileRecord;
	}

	/**
	 * 根据文件路径来删除文件记录
	 * 
	 * @param namespace 数据库名
	 * @param path 文件路径
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean deleteFileRecord(String namespace, String path) throws DBException,
			LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.deleteFileRecord(namespace, path);
	}

	/**
	 * 删除对应表的文件记录
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean deleteRecord(String namespace, String table, String path) throws DBException,
			LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.deleteRecordByPath(namespace, table, path);
	}

	/**
	 * 建立File对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createFileTable(String namespace) throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.createFiletable(namespace);
	}
}
