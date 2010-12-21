package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.TxtDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.TxtReader;
import com.searchlocal.util.StringUtils;

public class TxtService {

	public boolean execBatch(String namespace, int fileClassify) throws DBException,
			LogicException {
		TxtDao txtDao = new TxtDao();
		String txtpath = Constant.datapath + Constant.txtdatapath + fileClassify + Constant.suffixname;
		txtpath = txtpath.substring(1);
		txtpath = StringUtils.editFilePath(txtpath);

		txtDao.execbatch(txtpath, namespace);
		String existedpath = txtpath.substring(1, txtpath.length()-1);
		File txtfile = new File(existedpath);
		// 删除batch的数据文件
		if (txtfile.exists()) {
			txtfile.delete();
		}
		return true;
	}

	public int createBatchFile(TxtFileBean txtbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		TxtReader txtReader = new TxtReader();
		fileBeanList = txtReader.getTxtFile(txtbean.getPath());
		File txtfile = new File(Constant.datapath + Constant.txtdatapath + fileClassify + Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!txtfile.exists()) {
				txtfile.createNewFile();
			}
			out = new FileOutputStream(txtfile, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			TxtFileBean element = (TxtFileBean) iter.next();
			String temp = "";
			temp = txtbean.getFilename();
			String path = txtbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(txtbean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
			temp = temp + "," + String.valueOf(element.getRownb());
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

	public boolean insertTxtRecord(TxtFileBean element, String namespace)
			throws LogicException, DBException {
		List fileBeanList;
		TxtDao TxtDao;
		TxtReader txtReader = new TxtReader();
		fileBeanList = txtReader.getTxtFile(element.getPath());
		TxtDao = new TxtDao();
		return TxtDao.insertTxtRecord(fileBeanList, element.getPath(), element
				.getLastmodify(), element.getFilename(), namespace);
	}

	public boolean createTxtTable(String namespace) throws DBException,
			LogicException {
		TxtDao TxtDao;
		TxtDao = new TxtDao();
		return TxtDao.createTxttable(namespace);
	}
}
