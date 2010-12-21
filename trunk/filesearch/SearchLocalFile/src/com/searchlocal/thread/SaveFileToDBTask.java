package com.searchlocal.thread;

import java.io.File;

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
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.TxtService;
import com.searchlocal.service.WordService;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.StringUtils;

/**
 * 从文件容器取出文件插入数据库
 * 
 * <p>Title: 从文件容器取出文件插入数据库</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SaveFileToDBTask extends CRunnable {

	/** 搜索参数 */
	private CreateNewParam param;

	/** 文件容器 */
	private FileContainer filecon;

	/** 文件区分 */
	private int fileClassify;

	/** WordSQL个数 */
	private static int WORD_NUM_OF_SQL = 0;

	/** PptSQL个数 */
	private static int PPT_NUM_OF_SQL = 0;

	/** ExcelSQL个数 */
	private static int EXCEL_NUM_OF_SQL = 0;

	/** HTMLSQL个数 */
	private static int HTML_NUM_OF_SQL = 0;

	/** SRCSQL个数 */
	private static int SRC_NUM_OF_SQL = 0;

	/** PdfSQL个数 */
	private static int PDF_NUM_OF_SQL = 0;

	/** ChmSQL个数 */
	private static int CHM_NUM_OF_SQL = 0;

	/** SQL最大行数 */
	private final static int MAX_OF_SQL = 200;

	/** SRCSQL最大个数 */
	private static int SRC_MAX_NUM_OF_SQL = 10000;

	/** 
	 * 初始化
	 * 
	 * @param param 搜索参数
	 * @param filecon 文件容器
	 */
	public void init(CreateNewParam param, FileContainer filecon, int fileClassify) {
		this.param = param;
		this.filecon = filecon;
		this.fileClassify = fileClassify;
	}

	public void setTimeOut() {
	}

	/** 
	 * 执行
	 */
	public void run() {
		while (true) {
			ThreadUtil.sleep(100);
			File file = null;
			// 从文件容器中取出文件
			synchronized (this) {
				FileParam param = filecon.getfile();
				if(null != param){
					file = new File(param.getPath());
					// 读取文件存入DB
					if (null != file) {
						getFile(file);
					}
				}
			}
		}
	}

	/** 
	 * 文件内容存入DB
	 * 
	 * @param file 文件
	 */
	public boolean getFile(File file) {
		String filename = file.getName();
		String filepath = file.getAbsolutePath();
		String suffixname = StringUtils.suffixName(filepath);
		long lastmodify = file.lastModified();
		String absolutepath = file.getAbsolutePath();
		WordService wordservice = new WordService();
		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)) {
			WordFileBean filebean = new WordFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = wordservice.createBatchFile(filebean, param.getSearchname(), fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			WORD_NUM_OF_SQL = WORD_NUM_OF_SQL + sqlsize;
			if (WORD_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					wordservice.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				WORD_NUM_OF_SQL = 0;
			}
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			ExcelService excelService = new ExcelService();
			ExcelFileBean filebean = new ExcelFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = excelService.createBatchFile(filebean, param.getSearchname(),
						fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			EXCEL_NUM_OF_SQL = EXCEL_NUM_OF_SQL + sqlsize;
			if (EXCEL_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					excelService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				EXCEL_NUM_OF_SQL = 0;
			}
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			PdfService pdfService = new PdfService();
			PdfFileBean filebean = new PdfFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = pdfService.createBatchFile(filebean, param.getSearchname(), fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			PDF_NUM_OF_SQL = PDF_NUM_OF_SQL + sqlsize;
			if (PDF_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					pdfService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				PDF_NUM_OF_SQL = 0;
			}
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007) ) {
			PptService pptService = new PptService();
			PptFileBean filebean = new PptFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = pptService.createBatchFile(filebean, param.getSearchname(), fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			PPT_NUM_OF_SQL = PPT_NUM_OF_SQL + sqlsize;
			if (PPT_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					pptService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				PPT_NUM_OF_SQL = 0;
			}
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			ChmService chmService = new ChmService();
			ChmFileBean filebean = new ChmFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = chmService.createBatchFile(filebean, param.getSearchname(), fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			CHM_NUM_OF_SQL = CHM_NUM_OF_SQL + sqlsize;
			if (CHM_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					chmService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				CHM_NUM_OF_SQL = 0;
			}
		}
		if (Constant.FileClassify.isHtmlcontain(suffixname)) {
			HtmlService htmlService = new HtmlService();
			HtmlFileBean filebean = new HtmlFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = htmlService.createBatchFile(filebean, param.getSearchname(),
						fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			HTML_NUM_OF_SQL = HTML_NUM_OF_SQL + sqlsize;
			if (HTML_NUM_OF_SQL > MAX_OF_SQL) {
				try {
					htmlService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				HTML_NUM_OF_SQL = 0;
			}
			
//			HtmlService htmlService = new HtmlService();
//			HtmlFileBean filebean = new HtmlFileBean();
//			filebean.setFilename(filename);
//			filebean.setLastmodify(lastmodify);
//			filebean.setPath(absolutepath);
//			try {
//				boolean insert = false;
//				insert = htmlService.insertHtmlRecord(filebean, param.getSearchname());
//				if (insert) {
//					filecon.putinsertedfile(absolutepath, lastmodify);
//				}
//			} catch (DBException e) {
//				ExceptionHandler.getErrorList().add(e.getMessageKey());
//				filecon.puthaserrorfile(absolutepath, lastmodify);
//			} catch (LogicException e) {
//				ExceptionHandler.getErrorList().add(e.getMessageKey());
//				filecon.puthaserrorfile(absolutepath, lastmodify);
//			}
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			TxtService txtService = new TxtService();
			TxtFileBean filebean = new TxtFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = txtService.createBatchFile(filebean, param.getSearchname(), fileClassify);
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
			SRC_NUM_OF_SQL = SRC_NUM_OF_SQL + sqlsize;
			if (SRC_NUM_OF_SQL > SRC_MAX_NUM_OF_SQL) {
				try {
					txtService.execBatch(param.getSearchname(), fileClassify);
				} catch (DBException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (LogicException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				SRC_NUM_OF_SQL = 0;
			}
		}

		return true;
	}

	/** 
	 * 文件内容存入DB
	 * 
	 * @param file 文件
	 */
	public boolean getFileUseCommand(File file) {
		String filename = file.getName();
		String filepath = file.getAbsolutePath();
		String suffixname = StringUtils.suffixName(filepath);
		long lastmodify = file.lastModified();
		String absolutepath = file.getAbsolutePath();
		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)) {
			WordService wordservice = new WordService();
			WordFileBean filebean = new WordFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			boolean insert = false;
			try {
				insert = wordservice.insertWordRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (suffixname.equals(Constant.FileClassify.XLS)|| suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			ExcelService excelService = new ExcelService();
			ExcelFileBean filebean = new ExcelFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = excelService.insertExcelRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			PdfService pdfService = new PdfService();
			PdfFileBean filebean = new PdfFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = pdfService.insertPdfRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007)) {
			PptService pptService = new PptService();
			PptFileBean filebean = new PptFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = pptService.insertPptRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			ChmService chmService = new ChmService();
			ChmFileBean filebean = new ChmFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = chmService.insertChmRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (Constant.FileClassify.isHtmlcontain(suffixname)) {
			HtmlService htmlService = new HtmlService();
			HtmlFileBean filebean = new HtmlFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = htmlService.insertHtmlRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			TxtService txtService = new TxtService();
			TxtFileBean filebean = new TxtFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				boolean insert = false;
				insert = txtService.insertTxtRecord(filebean, param.getSearchname());
				if (insert) {
					filecon.putinsertedfile(absolutepath, lastmodify);
				}
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		return true;
	}

	/**
	 * @return Returns the param.
	 */
	private void createnewthread(String absolutepath) {
		// this.init(this.getFile(), param);
		// ThreadManager.getThreadManager().executeThread(this);
		// 线程有以下几种状态：NEW（已创建但尚未开始执行）、RUNNABLE（正在Java虚拟机中执行）、
		// BLOCKED（阻塞中：正等待获得监控锁）、WAITING（等待：无条件等候其他线程执行完毕，直到接收到唤醒通知）、
		// TIMED_WAITING（限时等待：等候其他线程执行完毕，直到接收到唤醒通知或等待时间超过了时限）、TERMINATED（终止：线程已经退出）。
	}

	/**
	 * @return Returns the param.
	 */
	public CreateNewParam getParam() {
		return param;
	}

	/**
	 * @param param
	 *            The param to set.
	 */
	public void setParam(CreateNewParam param) {
		this.param = param;
	}
}
