package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.PptFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.PptDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.PptReader;
import com.searchlocal.util.StringUtils;

public class PptService {

	public boolean execBatch(String namespace, String pptpath) throws DBException,
			LogicException {
		PptDao pptDao = new PptDao();
		pptpath = StringUtils.editFilePath(pptpath);

		pptDao.execbatch(pptpath, namespace);
		File pptfile = new File(pptpath);
		// 删除batch的数据文件
		if (pptfile.exists()) {
			pptfile.delete();
		}
		return true;
	}

	public int createBatchFile(PptFileBean pptbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		PptReader reader = new PptReader();
		fileBeanList = reader.getPptFile(pptbean.getPath());
		File pptfile = new File(Constant.datapath + Constant.pptdatapath + fileClassify + Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!pptfile.exists()) {
				pptfile.createNewFile();
			}
			out = new FileOutputStream(pptfile, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			PptFileBean element = (PptFileBean) iter.next();
			String temp = "";
			temp = pptbean.getFilename();
			String path = pptbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(pptbean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
			temp = temp + "," + String.valueOf(element.getPage());
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

		return fileBeanList.size();
	}

	public boolean insertPptRecord(PptFileBean Pptbean, String namespace)
			throws LogicException, DBException {
		List fileBeanList;
		PptDao PptDao;
		PptDao = new PptDao();
		PptReader reader = new PptReader();
		fileBeanList = reader.getPptFile(Pptbean.getPath());
		return PptDao.insertPptRecord(fileBeanList, Pptbean.getPath(), Pptbean
				.getLastmodify(), Pptbean.getFilename(), namespace);
	}

	public boolean createPptTable(String namespace) throws LogicException,
			DBException {
		PptDao PptDao;
		PptDao = new PptDao();
		return PptDao.createPpttable(namespace);
	}
}
