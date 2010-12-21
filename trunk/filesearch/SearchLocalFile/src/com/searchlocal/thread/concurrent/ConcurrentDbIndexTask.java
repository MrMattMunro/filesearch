package com.searchlocal.thread.concurrent;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.bean.CurrentFileBean;
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
import com.searchlocal.lucene.CurrentIndexUtil;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.FileService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.TxtService;
import com.searchlocal.service.WordService;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.DateUtil;
import com.searchlocal.util.StringUtils;

/**
 * 同步文件与数据库任务
 * 
 * <p>Title: 同步文件与数据库任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentDbIndexTask extends CRunnable {

	/** 文件容器 */
	private ConcurrentFileContainer filecon;
	
	/** 单个搜索对象 */
	private CreateNewParam createNewParam;
	
	/** 停止线程 */
	private boolean runflag = true;

	public synchronized void stopthread(){
	  runflag = false;
   }

		
	/**
	 * 初期化操作
	 * 
	 * @param filecon 文件容器
	 */
	public void init(ConcurrentFileContainer filecon , CreateNewParam createNewParam ) {
		this.filecon = filecon;
		this.createNewParam = createNewParam;
	}

	public void setTimeOut() {
	}

	/**
	 * 线程执行
	 */
	public void run() {
		while (runflag) {
			// 线程退出
			boolean iscurrentdone = filecon.isIsdone();
			if(iscurrentdone){
				break;
			}
			synchronized (this) {
				ThreadUtil.sleep(100);
				// 取得文件容器中的DB文件
				int dbfilenum = filecon.getDbfiles().size();
				boolean canstart = filecon.getAbletostart();
				System.out.println("开始取得文件容器中的DB文件  " + dbfilenum);
				System.out.println("dbfilenum:  " + dbfilenum);
				// 可以开始同步并Db里的文件信息已经装载的场合下,考虑到DB可能没有数据的情况
				if (canstart) {
					String path = createNewParam.getPath();
					File file = new File(path);
					// 递归操作同步文件
					operateFile(file, createNewParam);

					// 文件不存在，DB里存在的场合
					ConcurrentHashMap<String, CurrentFileBean> deletedfiles = filecon.getDbfiles();
					Set<String> keyset = deletedfiles.keySet();
					for (String delpath : keyset) {
						ThreadUtil.sleep(100);
						CurrentFileBean currentFileBean = deletedfiles.get(delpath);
						File delfile = new File(delpath);
						// 文件不存在且没有做过DB文件容器中的文件没有做过同步
						if (!delfile.exists() && !currentFileBean.isHascurrent()) {
							System.out.println("文件不存在，DB里存在:" + delpath);
							FileService fileservice = new FileService();
							// 后缀名
							String suffixname = StringUtils.suffixName(delpath);
							String table = StringUtils.getTableName(suffixname);
							String searchname = createNewParam.getSearchname();
							try {
								// 删除记录
								fileservice.deleteRecord(searchname, table, delpath);
								fileservice.deleteFileRecord(searchname, delpath);
								
								// 删除索引
								CurrentIndexUtil.deleteDcoumentByPath(searchname, delpath);
								currentFileBean.setHascurrent(true);
							} catch (DBException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							} catch (LogicException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}
				}
				System.out.println("和文件系统中的文件比较  ！！！ 完成");
			}
		}
	}

	/**
	 * 操作搜索目录下的文件
	 * 根据DB是否存在，修改，更新来执行
	 * 
	 * @param file 搜索目录
	 * @param param 搜索参数
	 */
	public void operateFile(File file, CreateNewParam param) {

		if (file.isDirectory()) {
			File[] files = file.listFiles();
			if (files != null) {
				for (int i = 0; i < files.length; i++) {
					operateFile(files[i], param);
				}
			}
		} else {
			String filename = file.getName();
			String filepath = file.getAbsolutePath();
			Long lastModified = file.lastModified();
			String slastModified = DateUtil.getDateTime(lastModified);
			String database = param.getSearchname();
			
			FileService fileservice = new FileService();
			// 根据文件名取得文件的类型
			String type = StringUtils.getTypebyName(filename);
			// 后缀名
			String suffixname = StringUtils.suffixName(filepath);
			// 根据后缀名取得要操作的表
			String table = StringUtils.getTableName(suffixname);
			// 判断是否为搜索的类型
			List doctypeList = param.getSelectfiletype();
			
			ConcurrentHashMap<String, CurrentFileBean> dbfiles = filecon.getDbfiles();
			Set<String> dbfilekeys = dbfiles.keySet();
			
			if (dbfilekeys.contains(filepath)) {
				// DB中存在的场合且没有同步的场合
				CurrentFileBean currentFileBean= dbfiles.get(filepath);
				Long dblastmodified = currentFileBean.getLastmodify();
				String slastmodified = DateUtil.getDateTime(dblastmodified);
				boolean hascurrent = currentFileBean.isHascurrent();
				
				// 用户修改的场合
				if (!slastModified.equals(slastmodified) && !hascurrent) {
					try {
						System.out.println("存在文件的更新：" + filepath);
						
						// 对文件内容记录进行更新(先删除,后插入)
						fileservice.deleteRecord(database, table, filepath);
						insetNewRecord(suffixname, database, filename, lastModified, filepath, false);
						
						// 更新索引
						CurrentIndexUtil.deleteDcoumentByPath(database, filepath);
						filecon.getNeedindexfile().put(filepath, currentFileBean);
						//CurrentIndexUtil.makeIndexByPath(indexpath, database, filepath);
					} catch (DBException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (LogicException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				currentFileBean.setHascurrent(true);
			} else {
				// DB中不存在的场合，且是规定搜索的文件类型
				if (!"".equals(table) && doctypeList.contains(type)) {
					System.out.println("DB中不存在的场合:" + filename + "," + filepath);
					insetNewRecord(suffixname, database, filename, lastModified, filepath, true);
					// 追加索引
					CurrentFileBean currentFileBean= new CurrentFileBean();
					currentFileBean.setLastmodify(lastModified);
					filecon.getNeedindexfile().put(filepath, currentFileBean);
					// CurrentIndexUtil.makeIndexByPath(indexpath, database, filepath);
					
					// 同步索引Bean放入内存
					currentFileBean.setHascurrent(true);
					dbfiles.put(filepath, currentFileBean);
				}
			}
		}
	}

	/**
	 * 操作搜索目录下的
	 * 
	 * @param suffixname 后缀名
	 * @param database 数据库
	 * @param filename 文件名
	 * @param lastmodify 修改日期
	 * @param absolutepath 绝对路径
     * @param isnew 是否是新插入的记录
	 */
	public static boolean insetNewRecord(String suffixname, String database,
			String filename, Long lastmodify, String absolutepath, boolean isnew) {

		// 新建文件对象
		FileParam element = new FileParam();
		element.setPath(absolutepath);
		element.setLastModify(lastmodify);
		element.setError("0");

		if (suffixname.equals(Constant.FileClassify.DOC) || suffixname.equals(Constant.FileClassify.DOC2007)) {
			WordService wordservice = new WordService();
			WordFileBean filebean = new WordFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				wordservice.insertWordRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (suffixname.equals(Constant.FileClassify.XLS) || suffixname.endsWith(Constant.FileClassify.XLS2007)) {
			ExcelService excelService = new ExcelService();
			ExcelFileBean filebean = new ExcelFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				excelService.insertExcelRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (suffixname.equals(Constant.FileClassify.PDF)) {
			PdfService pdfService = new PdfService();
			PdfFileBean filebean = new PdfFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				pdfService.insertPdfRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (suffixname.equals(Constant.FileClassify.PPT) || suffixname.equals(Constant.FileClassify.PPT2007)) {
			PptService pptService = new PptService();
			PptFileBean filebean = new PptFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				pptService.insertPptRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (suffixname.equals(Constant.FileClassify.CHM)) {
			ChmService chmService = new ChmService();
			ChmFileBean filebean = new ChmFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				chmService.insertChmRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (Constant.FileClassify.isHtmlcontain(suffixname)) {
			HtmlService htmlService = new HtmlService();
			HtmlFileBean filebean = new HtmlFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				htmlService.insertHtmlRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		if (Constant.SrcClassify.iscontain(suffixname)) {
			TxtService txtService = new TxtService();
			TxtFileBean filebean = new TxtFileBean();
			filebean.setFilename(filename);
			filebean.setLastmodify(lastmodify);
			filebean.setPath(absolutepath);
			try {
				txtService.insertTxtRecord(filebean, database);
			} catch (DBException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} catch (LogicException e) {
				element.setError("1");
				ExceptionHandler.getErrorList().add(e.getMessageKey());
			} finally {
				insertFile(element, isnew, database);
			}
		}
		return true;
	}
	
	/**
	 * 插入文件记录
	 * 
	 * @param element 文件对象
	 * @param database 数据库
     * @param isnew 是否是新插入的记录
	 */
	public static void insertFile(FileParam element, boolean isnew, String database) {
		FileService fileservice = new FileService();
		List<FileParam> beanList = new ArrayList<FileParam>();
		beanList.add(element);
		try {
			// 新建的场合
			if (isnew) {
				fileservice.insertFileRecord(beanList, database);
			} else {
				// 更新的场合
				fileservice.updateFileRecord(beanList, database);
			}
		} catch (DBException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (LogicException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public CreateNewParam getCreateNewParam() {
		return createNewParam;
	}

	public void setCreateNewParam(CreateNewParam createNewParam) {
		this.createNewParam = createNewParam;
	}
}
