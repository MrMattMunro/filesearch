package com.searchlocal.thread;

import java.io.File;
import java.util.List;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.StringUtils;

/**
 * 搜索文件路径地址
 * 
 * <p>Title: 更新文件容器</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearchFilePathTask extends CRunnable {

	/** 文件路径 */
	private File file;

	/** 新建搜索对象参数 */
	private CreateNewParam param;

	/** 文件容器 */
	private FileContainer filecon;

	/** 
	 * 构造器
	 * 
	 * @param file 文件路径
	 * @param param 新建搜索对象参数
	 * @param filecon 文件容器
	 */
	public void init(File file, CreateNewParam param, FileContainer filecon) {
		this.file = file;
		this.param = param;
		this.filecon = filecon;
	}

	public File getFile() {
		return this.file;
	}

	public void setTimeOut() {
	}

	public void run() {
		getFile(file);
	}

	public void getFile(File file) {

		if (file.isDirectory()) {
			File[] files = file.listFiles();
			if (files != null) {
				for (int i = 0; i < files.length; i++) {
					getFile(files[i]);
				}
			}
		} else {
			ThreadUtil.sleep(20);
			List<String> typeList = param.getSelectfiletype();
			String filename = file.getName();
			String suffixname = StringUtils.suffixName(filename);

			if (typeList.contains("word")
					&& (suffixname.equals(Constant.FileClassify.DOC) || suffixname
							.equals(Constant.FileClassify.DOC2007))) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("excel")
					&& (suffixname.equals(Constant.FileClassify.XLS) || suffixname
							.endsWith(Constant.FileClassify.XLS2007))) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("pdf") && suffixname.equals(Constant.FileClassify.PDF)) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("ppt")
					&& (suffixname.equals(Constant.FileClassify.PPT) || suffixname
							.equals(Constant.FileClassify.PPT2007))) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("chm") && suffixname.equals(Constant.FileClassify.CHM)) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("html") && (Constant.FileClassify.isHtmlcontain(suffixname))) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
			if (typeList.contains("txt") && (Constant.SrcClassify.iscontain(suffixname))) {
				filecon.putfile(file.getAbsolutePath(), file.lastModified());
			}
		}
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
