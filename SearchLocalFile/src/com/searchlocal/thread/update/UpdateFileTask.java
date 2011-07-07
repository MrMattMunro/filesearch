/**
 * $RCSfile: UpdateFileTask.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread.update;

import java.io.File;
import java.util.List;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.UpdateParam;
import com.searchlocal.thread.base.CRunnable;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.StringUtils;

/**
 * 递归文件将需要处理的文件放入容器
 * 
 * <p>Title: 递归文件将需要处理的文件放入容器</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class UpdateFileTask extends CRunnable {

	/** 搜索对象路径 */
	private File file;

	/** 更新搜索对象时,数据存储对象 */
	private UpdateParam param;

	/** 更新文件容器 */
	private UpdateFileContainer filecon;

	/** 
	 * 构造器
	 * 
	 * @param file  搜索对象
	 * @param param 数据存储
	 * @param filecon 文件容器
	 */
	public void init(File file, UpdateParam param, UpdateFileContainer filecon) {
		this.file = file;
		this.param = param;
		this.filecon = filecon;
	}

	/** 
	 * 取得搜索对象
	 */
	public File getFile() {
		return this.file;
	}

	/** 
	 * 设置过时
	 */
	public void setTimeOut() {
	}

	/** 
	 * 执行部分
	 */
	public void run() {
		getFile(file);
	}

	/** 
	 * 执行部分
	 */
	public void getFile(File file) {
		// 递归
		if (file.isDirectory()) {
			File[] files = file.listFiles();
			if (files != null) {
				for (int i = 0; i < files.length; i++) {
					getFile(files[i]);
				}
			}
		} else {
			ThreadUtil.sleep(10);
			// 需要追加
			List<String> needAddTypeList = param.getNeedAddfiletypes();
			// 需要删除
			List<String> needDelTypeList = param.getNeedDelfiletypes();
			String filename = file.getName();
			String suffixname = StringUtils.suffixName(filename);

			// 判断是否需要添加
			if (needAddTypeList.contains("word") && (suffixname.equals(Constant.FileClassify.DOC) || suffixname
							.equals(Constant.FileClassify.DOC2007))) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("excel") && (suffixname.equals(Constant.FileClassify.XLS) || suffixname
							.endsWith(Constant.FileClassify.XLS2007))) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("pdf") && suffixname.equals(Constant.FileClassify.PDF)) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("ppt")
					&& (suffixname.equals(Constant.FileClassify.PPT) || suffixname
							.equals(Constant.FileClassify.PPT2007))) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("chm") && suffixname.equals(Constant.FileClassify.CHM)) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("html") && (Constant.FileClassify.isHtmlcontain(suffixname))) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needAddTypeList.contains("txt") && (Constant.SrcClassify.iscontain(suffixname))) {
				filecon.putAddfile(file.getAbsolutePath(), file.lastModified());
			}
			
			// 判断是否需要删除
			if (needDelTypeList.contains("word") && (suffixname.equals(Constant.FileClassify.DOC) || suffixname
							.equals(Constant.FileClassify.DOC2007))) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("excel") && (suffixname.equals(Constant.FileClassify.XLS) || suffixname
							.endsWith(Constant.FileClassify.XLS2007))) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("pdf") && suffixname.equals(Constant.FileClassify.PDF)) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("ppt")
					&& (suffixname.equals(Constant.FileClassify.PPT) || suffixname
							.equals(Constant.FileClassify.PPT2007))) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("chm") && suffixname.equals(Constant.FileClassify.CHM)) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("html") && (Constant.FileClassify.isHtmlcontain(suffixname))) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
			if (needDelTypeList.contains("txt") && (Constant.SrcClassify.iscontain(suffixname))) {
				filecon.putDelfile(file.getAbsolutePath(), file.lastModified());
			}
		}
	}
}
