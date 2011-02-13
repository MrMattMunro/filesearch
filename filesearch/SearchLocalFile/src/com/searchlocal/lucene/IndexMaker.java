package com.searchlocal.lucene;

import java.io.File;
import java.util.Iterator;
import java.util.Set;

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.bean.PptFileBean;
import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.exhander.ExceptionHandler;
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.TxtService;
import com.searchlocal.service.WordService;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

/**
 * 索引新建操作类
 * 
 * <p>Title: 索引操作</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class IndexMaker {

	/** 日志 */
	private static CLogger logger = new CLogger(IndexMaker.class);

	/**
	 * 生成索引文件
	 * 
	 * @param namespace 数据库名称
	 * @param paths 文件列表
	 * @return 是否成功
	 */
	public static boolean makeindex(String namespace, Set<String> paths) throws Exception {
		// 新建服务类
		WordService wordservice = new WordService();
		ExcelService excelService = new ExcelService();
		PdfService pdfService = new PdfService();
		PptService pptService = new PptService();
		ChmService chmService = new ChmService();
		HtmlService htmlService = new HtmlService();
		TxtService txtService = new TxtService();
		for (Iterator<String> iter = paths.iterator(); iter.hasNext();) {
			String path = (String)iter.next();
			File file = new File(path);
			String filename = file.getName();
			String filepath = file.getAbsolutePath();
			String suffixname = StringUtils.suffixName(filepath);
			long lastmodify = file.lastModified();
			String absolutepath = file.getAbsolutePath();
			// 文件是Word的场合
			if ((suffixname.equals(Constant.FileClassify.DOC)
					|| suffixname.equals(Constant.FileClassify.DOC2007))&& StringUtils.isNotTempDoc(filename)) {
				WordFileBean filebean = new WordFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					wordservice.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Excel的场合
			if ((suffixname.equals(Constant.FileClassify.XLS)
					|| suffixname.endsWith(Constant.FileClassify.XLS2007))&& StringUtils.isNotTempDoc(filename)) {
				ExcelFileBean filebean = new ExcelFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					excelService.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Pdf的场合
			if (suffixname.equals(Constant.FileClassify.PDF)) {
				PdfFileBean filebean = new PdfFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					pdfService.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Ppt的场合
			if ((suffixname.equals(Constant.FileClassify.PPT)
					|| suffixname.endsWith(Constant.FileClassify.PPT2007))&& StringUtils.isNotTempDoc(filename))  {
				PptFileBean filebean = new PptFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					pptService.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Chm的场合
			if (suffixname.equals(Constant.FileClassify.CHM)) {
				ChmFileBean filebean = new ChmFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					chmService.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Html的场合
			if (Constant.FileClassify.isHtmlcontain(suffixname)) {
				HtmlFileBean filebean = new HtmlFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					 htmlService.createIndex(filebean, namespace);
				} catch (DBException e) {
					e.printStackTrace();
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					e.printStackTrace();
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
			// 文件是Src的场合
			if (Constant.SrcClassify.iscontain(suffixname)) {
				TxtFileBean filebean = new TxtFileBean();
				filebean.setFilename(filename);
				filebean.setLastmodify(lastmodify);
				filebean.setPath(absolutepath);
				try {
					txtService.createIndex(filebean, namespace);
				} catch (DBException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				} catch (LogicException e) {
					ExceptionHandler.getErrorList().add(e.getMessageKey());
				}
			}
		}
		return true;
	}
}
