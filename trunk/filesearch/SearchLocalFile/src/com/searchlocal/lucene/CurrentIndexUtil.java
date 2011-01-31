package com.searchlocal.lucene;

import java.io.File;
import java.io.IOException;
import java.util.List;

import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.Term;

import com.searchlocal.bean.ChangInfoBean;
import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.bean.PptFileBean;
import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.filereader.ChmReader;
import com.searchlocal.filereader.ExcelReader;
import com.searchlocal.filereader.HtmlReader;
import com.searchlocal.filereader.PdfReader;
import com.searchlocal.filereader.PptReader;
import com.searchlocal.filereader.TxtReader;
import com.searchlocal.filereader.WordReader;
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.TxtService;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

/**
 * 索引更新操作类
 * 
 * <p>Title: 索引更新操作</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CurrentIndexUtil {

	/** 日志 */
	private static CLogger logger = new CLogger(CurrentIndexUtil.class);

	/**
	 * 构造器
	 */
	public CurrentIndexUtil() {
		super();
	}

	/**
	 * 根据文件路径删除索引文件中内容
	 * 
	 * @param dir 索引路径
	 * @param path 需要删除的文件路径
	 */
	public static void deleteDcoumentByPath(String searcher, String path) {
		try {
			// 删除
			IndexReaderFactory indexWriterFactory = new IndexReaderFactory();
			indexWriterFactory.deleteDocuments(searcher, new Term("path", path));
		} catch (CorruptIndexException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	* 根据文件路径把文件追加索引
	*
	*@param nameapce  数据库名
	*@param changinfo 需要追加入索引的文件
	*/
	public static void makeIndexByPath(String namespace, ChangInfoBean changeInfo) {
		try {
			// 文件路径
			String path = changeInfo.getPath();

			// 最后修改时间
			long lastmodify = changeInfo.getLastmodify();
			// 后缀名
			String suffixname = StringUtils.suffixName(path);
			// 文件名
			String filename = StringUtils.getFileNameByPath(path);
			// 新建读取对象
			WordReader wordreader = new WordReader();
			ExcelReader excelreader = new ExcelReader();
			PdfReader pdfreader = new PdfReader();
			PptReader pptreader = new PptReader();
			ChmReader chmreader = new ChmReader();
			TxtReader txtreader = new TxtReader();
			HtmlReader htmlreader = new HtmlReader();
			// 当时Word的情况下
			if ((suffixname.equals(Constant.FileClassify.DOC) || suffixname
					.equals(Constant.FileClassify.DOC2007))) {

				// 建立WordBean对象
				WordFileBean filebean = new WordFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				
				// 取得文档内容
				List<WordFileBean> fileBeanList = wordreader.getWordFile(filebean);
				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.WORD, fileBeanList);
			}
			if (suffixname.equals(Constant.FileClassify.XLS)
					|| suffixname.endsWith(Constant.FileClassify.XLS2007)) {
				// 建立ExcelBean对象
				ExcelFileBean filebean = new ExcelFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<ExcelFileBean> fileBeanList = excelreader.getExcelFile(filebean);
				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.EXCEL, fileBeanList);
			}
			if (suffixname.equals(Constant.FileClassify.PDF)) {
				// 建立PdfBean对象
				PdfFileBean filebean = new PdfFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<PdfFileBean> fileBeanList = pdfreader.getPdfFile(filebean);
				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.PDF, fileBeanList);
			}
			if (suffixname.equals(Constant.FileClassify.PPT)
					|| suffixname.equals(Constant.FileClassify.PPT2007)) {
				// 建立PptBean对象
				PptFileBean filebean = new PptFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<PptFileBean> fileBeanList = pptreader.getPptFile(filebean);
				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.PPT, fileBeanList);
			}
			if (suffixname.equals(Constant.FileClassify.CHM)) {
				// 建立ChmBean对象
				ChmFileBean filebean = new ChmFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<ChmFileBean> fileBeanList = chmreader.getChmFile(filebean);

				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.CHM, fileBeanList);
			}
			if (Constant.FileClassify.isHtmlcontain(suffixname)) {
				// 建立HtmlBean对象
				HtmlFileBean filebean = new HtmlFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<HtmlFileBean> fileBeanList = htmlreader.getHtmlFile(filebean);
				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.HTML, fileBeanList);
			}
			if (Constant.SrcClassify.iscontain(suffixname)) {
				// 建立TxtBean对象
				TxtFileBean filebean = new TxtFileBean();
				filebean.setPath(path);
				filebean.setLastmodify(lastmodify);
				filebean.setFilename(filename);
				// 取得文档内容
				List<TxtFileBean> fileBeanList = txtreader.getTxtFile(filebean);

				// 建立索引
				IndexBeanList.makeindex(namespace, Constant.FileNameClassify.TXT, fileBeanList);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
