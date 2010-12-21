package com.searchlocal.service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.dao.PdfDao;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.filereader.PdfReader;
import com.searchlocal.util.StringUtils;

public class PdfService {

	public boolean execBatch(String namespace, int fileClassify) throws DBException,
			LogicException {
		PdfDao pdfDao = new PdfDao();
		String pdfpath = Constant.datapath + Constant.pdfdatapath + fileClassify + Constant.suffixname;
		pdfpath = pdfpath.substring(1);
		pdfpath = StringUtils.editFilePath(pdfpath);

		pdfDao.execbatch(pdfpath, namespace);
		String existedpath = pdfpath.substring(1, pdfpath.length()-1);
		File pdffile = new File(existedpath);
		// 删除batch的数据文件
		if (pdffile.exists()) {
			pdffile.delete();
		}
		return true;
	}

	public int createBatchFile(PdfFileBean pdfbean, String namespace,
			int fileClassify) throws DBException, LogicException {
		List fileBeanList;
		PdfReader reader = new PdfReader();
		fileBeanList = reader.getPdfFile(pdfbean.getPath());
		File pdffile = new File(Constant.datapath + Constant.pdfdatapath + fileClassify + Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!pdffile.exists()) {
				pdffile.createNewFile();
			}
			out = new FileOutputStream(pdffile, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		for (Iterator iter = fileBeanList.iterator(); iter.hasNext();) {
			PdfFileBean element = (PdfFileBean) iter.next();
			String temp = "";
			temp = pdfbean.getFilename();
			String path = pdfbean.getPath();
			path = StringUtils.editFilePathForBatch(path);
			temp = temp + "," + path;
			temp = temp + "," + new Timestamp(pdfbean.getLastmodify());
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

	public boolean insertPdfRecord(PdfFileBean Pdfbean, String namespace)
			throws LogicException, DBException {
		List fileBeanList;
		PdfDao PdfDao;
		PdfDao = new PdfDao();
		PdfReader reader = new PdfReader();
		fileBeanList = reader.getPdfFile(Pdfbean.getPath());
		return PdfDao.insertPdfRecord(fileBeanList, Pdfbean.getPath(), Pdfbean
				.getLastmodify(), Pdfbean.getFilename(), namespace);
	}

	public boolean createPdfTable(String namespace) throws LogicException,
			DBException {
		PdfDao PdfDao;
		PdfDao = new PdfDao();
		return PdfDao.createPdftable(namespace);
	}
}
