package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.WordDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.WordReader;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.StringUtils;

public class WordService {

	public boolean insertWordRecord(WordFileBean wordbean, String namespace)
			throws DBException, LogicException {
		List fileBeanList;
		WordDao wordDao;
		wordDao = new WordDao();
		WordReader reader = new WordReader();
		fileBeanList = reader.getWordFile(wordbean.getPath());
		return wordDao.insertWordRecord(fileBeanList, wordbean.getPath(),
				wordbean.getLastmodify(), wordbean.getFilename(), namespace);
	}

	public boolean execBatch(String namespace, String cvspath) throws DBException,
			LogicException {
		WordDao wordDao = new WordDao();
		cvspath = StringUtils.editFilePath(cvspath);

		wordDao.execbatch(cvspath, namespace);
		File wordfile = new File(cvspath);
		// 删除batch的数据文件 
		if (wordfile.exists()) {
			wordfile.delete();
		}
		return true;
	}

	public int createBatchFile(WordFileBean wordbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		WordReader reader = new WordReader();
		fileBeanList = reader.getWordFile(wordbean.getPath());
		FileOutputStream out = FileUtil.getFileStreamOut(Constant.worddatapath, fileClassify);

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			WordFileBean element = (WordFileBean) iter.next();
			String temp = "";
			temp = wordbean.getFilename();
			String path = wordbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(wordbean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
			temp = temp + "," + String.valueOf(element.getParagraphNo());
			temp = temp + "\r\n";
			try {
				out.write(temp.getBytes("utf-8"));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		try {
			if (out != null) {
				out.close();
				out = null;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return fileBeanList.size();
	}

	public boolean createWordTable(String namespace) throws LogicException,
			DBException {
		WordDao wordDao;
		wordDao = new WordDao();
		return wordDao.createWordtable(namespace);
	}
}
