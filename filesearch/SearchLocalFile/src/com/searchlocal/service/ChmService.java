package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.ChmDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.ChmReader;
import com.searchlocal.util.StringUtils;

public class ChmService {

	public boolean execBatch(String namespace, String chmpath) throws DBException,
			LogicException {
		ChmDao chmDao = new ChmDao();
		chmpath = StringUtils.editFilePath(chmpath);

		chmDao.execbatch(chmpath, namespace);
		File chmfile = new File(chmpath);
		// 删除batch的数据文件
		if (chmfile.exists()) {
			chmfile.delete();
		}
		return true;
	}

	public int createBatchFile(ChmFileBean chmbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		ChmReader chmReader = new ChmReader();
		fileBeanList = chmReader.getChmFile(chmbean.getPath());

		File wordfile = new File(Constant.datapath + Constant.chmdatapath + fileClassify + Constant.suffixname);
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

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			ChmFileBean element = (ChmFileBean) iter.next();
			String temp = "";
			temp = chmbean.getFilename();
			String path = chmbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(chmbean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
			temp = temp + "," + String.valueOf(element.getCatalogname());
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

	public boolean insertChmRecord(ChmFileBean chmbean, String namespace)
			throws DBException, LogicException {
		ChmDao ChmDao;
		ChmDao = new ChmDao();
		ChmReader chmReader = new ChmReader();
		List fileBeanList = chmReader.getChmFile(chmbean.getPath());
		return ChmDao.insertChmRecord(fileBeanList, chmbean.getPath(), chmbean
				.getLastmodify(), chmbean.getFilename(), namespace);
	}

	public boolean createChmTable(String namespace) throws DBException,
			LogicException {
		ChmDao ChmDao;
		ChmDao = new ChmDao();
		return ChmDao.createChmtable(namespace);
	}
}
