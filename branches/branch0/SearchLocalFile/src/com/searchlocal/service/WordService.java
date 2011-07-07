package com.searchlocal.service;

import java.io.File;
import java.util.List;

import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.WordDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.WordReader;
import com.searchlocal.lucene.IndexBeanList;
import com.searchlocal.util.StringUtils;

/**
 * Word文件服务类
 * 
 * <p>Title: Txt及代码文件服务类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class WordService {

	/**
	 * 对Word文件建立索引
	 * 
	 * @param pptbean Word文件Bean
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public int createIndex(WordFileBean wordbean, String namespace) throws DBException,
			LogicException {
		WordReader reader = new WordReader();
		List<WordFileBean> fileBeanList = reader.getWordFile(wordbean);
		IndexBeanList.makeindex(namespace, Constant.FileNameClassify.WORD, fileBeanList);
		return fileBeanList.size();
	}

	/**
	 * 创建Word表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createWordTable(String namespace) throws LogicException, DBException {
		WordDao wordDao;
		wordDao = new WordDao();
		return wordDao.createWordtable(namespace);
	}

	/**
	 * 执行Batch文件
	 * 
	 * @param namespace 数据库名
	 * @param cvspath csv文件
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean execBatch(String namespace, String cvspath) throws DBException, LogicException {
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
}
