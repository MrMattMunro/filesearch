package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.HtmlDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.HtmlReader;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.StringUtils;

public class HtmlService {

	public boolean execBatch(String namespace, int fileClassify) throws DBException,
			LogicException {
		HtmlDao htmlDao = new HtmlDao();
		String htmlpath = Constant.datapath + Constant.htmldatapath+ fileClassify + Constant.suffixname;
		htmlpath = htmlpath.substring(1);
		htmlpath = StringUtils.editFilePath(htmlpath);

		htmlDao.execbatch(htmlpath, namespace);
		String existedpath = htmlpath.substring(1, htmlpath.length()-1);
		File htmlfile = new File(existedpath);
		// 删除batch的数据文件
		if (htmlfile.exists()) {
			htmlfile.delete();
		}
		return true;
	}

	public int createBatchFile(HtmlFileBean htmlBean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		HtmlReader reader = new HtmlReader();
		fileBeanList = reader.getHtmlFile(htmlBean.getPath());
		FileOutputStream out = FileUtil.getFileStreamOut(Constant.htmldatapath, fileClassify);
		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			HtmlFileBean element = (HtmlFileBean) iter.next();
			String temp = "";
			temp = htmlBean.getFilename();
			String path = htmlBean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(htmlBean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
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

	public boolean insertHtmlRecord(HtmlFileBean element, String namespace)
			throws LogicException, DBException {
		List fileBeanList;
		HtmlDao HtmlDao;
		HtmlReader reader = new HtmlReader();
		fileBeanList = reader.getHtmlFile(element.getPath());
		HtmlDao = new HtmlDao();
		return HtmlDao.insertHtmlRecord(fileBeanList, element.getPath(),
				element.getLastmodify(), element.getFilename(), namespace);
	}

	public boolean createHtmlTable(String namespace) throws LogicException,
			DBException {
		HtmlDao HtmlDao;
		HtmlDao = new HtmlDao();
		return HtmlDao.createHtmltable(namespace);
	}
}
