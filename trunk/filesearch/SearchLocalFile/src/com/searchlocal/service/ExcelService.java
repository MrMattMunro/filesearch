package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.ExcelDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.ExcelReader;
import com.searchlocal.util.StringUtils;

public class ExcelService {

	public boolean execBatch(String namespace, String csvpath) throws DBException,
			LogicException {
		ExcelDao excelDao = new ExcelDao();
		csvpath = StringUtils.editFilePath(csvpath);

		excelDao.execbatch(csvpath, namespace);
		File excelfile = new File(csvpath);
		// 删除batch的数据文件
		if (excelfile.exists()) {
			excelfile.delete();
		}
		return true;
	}

	public int createBatchFile(ExcelFileBean excelbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		ExcelReader reader = new ExcelReader();
		fileBeanList = reader.getExcelFile(excelbean.getPath());
		File excelfile = new File(Constant.datapath + Constant.exceldatapath + fileClassify + Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!excelfile.exists()) {
				excelfile.createNewFile();
			}
			out = new FileOutputStream(excelfile, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			ExcelFileBean element = (ExcelFileBean) iter.next();
			String temp = "";
			temp = excelbean.getFilename();
			String path = excelbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(excelbean.getLastmodify());
			String content = element.getContent();
			content = StringUtils.replaceRN(content);
			temp = temp + "," + content;
			temp = temp + "," + String.valueOf(element.getSheetname());
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

	public boolean insertExcelRecord(ExcelFileBean element, String namespace)
			throws LogicException, DBException {
		List fileBeanList;
		ExcelDao excelDao;
		ExcelReader reader = new ExcelReader();
		fileBeanList = reader.getExcelFile(element.getPath());
		excelDao = new ExcelDao();
		return excelDao.insertExcelRecord(fileBeanList, element.getPath(),
				element.getLastmodify(), element.getFilename(), namespace);
	}

	public boolean createExcelTable(String namespace) throws DBException,
			LogicException {
		ExcelDao excelDao;
		excelDao = new ExcelDao();
		return excelDao.createExceltable(namespace);
	}
}
