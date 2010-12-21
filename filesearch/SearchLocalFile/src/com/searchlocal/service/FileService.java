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

public class FileService {

	public boolean execBatch(String namespace) throws DBException,
			LogicException {
		FileDao fileDao = new FileDao();
		String filepath = Constant.datapath + Constant.filedatapath+ Constant.suffixname;
		filepath = filepath.substring(1);
		filepath = StringUtils.editFilePath(filepath);

		fileDao.execbatch(filepath, namespace);
		String existedpath = filepath.substring(1, filepath.length()-1);
		File file = new File(existedpath);
		// 删除batch的数据文件
		if (file.exists()) {
			file.delete();
		}
		return true;
	}

	public int createBatchFile(List filebeanList, String namespace,
			int fileClassify) throws DBException, LogicException {
		File wordfile = new File(Constant.datapath + Constant.filedatapath + fileClassify + Constant.suffixname);
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

		for (Iterator iter = filebeanList.iterator(); iter.hasNext();) {
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
		try {
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return filebeanList.size();
	}

	public boolean insertFileRecord(List beanList, String namespace)
			throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.insertFileRecord(beanList, namespace);
	}

	public boolean updateFileRecord(List beanList, String namespace)
			throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.updateFileRecord(beanList, namespace);
	}

	public List<FileParam> getFileRecordList(String namespace)
			throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		List<FileParam> fileRecord = fileDao.getFileRecord(namespace);
		return fileRecord;
	}

	public boolean deleteFileRecord(String namespace, String path)
			throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.deleteFileRecord(namespace, path);
	}

	public boolean deleteRecord(String namespace, String table, String path)
			throws DBException, LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.deleteRecordByPath(namespace, table, path);
	}

	public boolean createFileTable(String namespace) throws DBException,
			LogicException {
		FileDao fileDao;
		fileDao = new FileDao();
		return fileDao.createFiletable(namespace);
	}
}
