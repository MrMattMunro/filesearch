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
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CreateIndexTask extends CRunnable {

	/** 搜索参数 */
	private CreateNewParam param;

	/** 文件容器 */
	private FileContainer filecon;

	/** 
	 * 初始化
	 * 
	 * @param param 搜索参数
	 * @param filecon 文件容器
	 */
	public void init(CreateNewParam param, FileContainer filecon) {
		this.param = param;
		this.filecon = filecon;
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
				if (null != param) {
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
		if ((suffixname.equals(Constant.FileClassify.DOC)
				|| suffixname.equals(Constant.FileClassify.DOC2007))&& StringUtils.isNotTempDoc(filename)) {
			WordFileBean filebean = new WordFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = wordservice.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}

		if ((suffixname.equals(Constant.FileClassify.XLS)
				|| suffixname.endsWith(Constant.FileClassify.XLS2007))&& StringUtils.isNotTempDoc(filename)) {
			ExcelService excelService = new ExcelService();
			ExcelFileBean filebean = new ExcelFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = excelService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
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
			int sqlsize = 0;
			try {
				sqlsize = pdfService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			}
		}
		if ((suffixname.equals(Constant.FileClassify.PPT)
				|| suffixname.endsWith(Constant.FileClassify.PPT2007))&& StringUtils.isNotTempDoc(filename))  {
			PptService pptService = new PptService();
			PptFileBean filebean = new PptFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			int sqlsize = 0;
			try {
				sqlsize = pptService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
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
			int sqlsize = 0;
			try {
				sqlsize = chmService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
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
			int sqlsize = 0;
			try {
				sqlsize = htmlService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
			} catch (DBException e) {
				e.printStackTrace();
				ExceptionHandler.getErrorList().add(e.getMessageKey());
				filecon.puthaserrorfile(absolutepath, lastmodify);
			} catch (LogicException e) {
				e.printStackTrace();
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
			int sqlsize = 0;
			try {
				sqlsize = txtService.createIndex(filebean, param.getSearchname());
				filecon.putinsertedfile(absolutepath, lastmodify);
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
