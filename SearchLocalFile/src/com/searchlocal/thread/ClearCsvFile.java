package com.searchlocal.thread;

import java.io.File;

import com.searchlocal.constants.Constant;
import com.searchlocal.dao.ChmDao;
import com.searchlocal.dao.ExcelDao;
import com.searchlocal.dao.HtmlDao;
import com.searchlocal.dao.PdfDao;
import com.searchlocal.dao.PptDao;
import com.searchlocal.dao.TxtDao;
import com.searchlocal.dao.WordDao;
import com.searchlocal.util.StringUtils;

/**
 * 清理CSV插入到DB
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public final class ClearCsvFile {

	public static boolean saveCsvToDB(String datapath, String namespace) {
		File csvDir = new File(datapath);
		File[] files = csvDir.listFiles();
		try {
			for (int i = 0; i < files.length; i++) {
				File file = files[i];
				String filename = file.getName();
				filename = filename.substring(0, filename.length() - 5);

				String csvfilepath = StringUtils.editFilePath(file.getAbsolutePath());

				if (Constant.worddatapath.indexOf(filename) != -1) {
					WordDao wordDao = new WordDao();
					wordDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.exceldatapath.indexOf(filename) != -1) {
					ExcelDao excelDao = new ExcelDao();
					excelDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.pptdatapath.indexOf(filename) != -1) {
					PptDao pptDao = new PptDao();
					pptDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.pdfdatapath.indexOf(filename) != -1) {
					PdfDao pdfDao = new PdfDao();
					pdfDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.htmldatapath.indexOf(filename) != -1) {
					HtmlDao htmlDao = new HtmlDao();
					htmlDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.txtdatapath.indexOf(filename) != -1) {
					TxtDao txtDao = new TxtDao();
					txtDao.execbatch(csvfilepath, namespace);
				}
				if (Constant.chmdatapath.indexOf(filename) != -1) {
					ChmDao chmDao = new ChmDao();
					chmDao.execbatch(csvfilepath, namespace);
				}
				// 删除batch的数据文件
				if (file.exists()) {
					file.delete();
				}
			}

			File[] htmlfiles = csvDir.listFiles();
			for (int i = 0; i < htmlfiles.length; i++) {
				File file = htmlfiles[i];
				String filename = file.getName();
				filename = filename.substring(0, filename.length() - 5);

				String csvfilepath = StringUtils.editFilePath(file.getAbsolutePath());

				if (Constant.htmldatapath.indexOf(filename) != -1) {
					HtmlDao htmlDao = new HtmlDao();
					htmlDao.execbatch(csvfilepath, namespace);
				}
				// 删除html生成的batch的数据文件
				if (file.exists()) {
					file.delete();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		return true;
	}

}
