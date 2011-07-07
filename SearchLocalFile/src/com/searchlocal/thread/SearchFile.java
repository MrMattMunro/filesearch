/**
 * $RCSfile: SearchFile.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.thread;

import java.io.File;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.FileUtil;

/**
 * 搜索并建立索引
 * 
 * <p>Title: 搜索并建立索引</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearchFile {

	/** 文件容器 */
	private static FileContainer filecon = null;

	/**
	 * 搜索文件存入文件容器
	 * 
	 * @param param 搜索参数
	*/
	public void listen(CreateNewParam param) {
		try {
			// 文件路径
			String path = param.getPath();

			// 取得适合的并发数
			int threadnum = FileUtil.getSubFileNums(path);
			// 新建文件容器
			filecon = new FileContainer();
			// 取得文件对象
			File file = new File(path);

			// 实行搜索文件路径
			SearchFilePathTask searchpathtask = new SearchFilePathTask();
			searchpathtask.init(file, param, filecon);
			ThreadCheckThreadManager.getThreadManager().executeThread(searchpathtask);

			// 开始把文件写入索引文件
			FileUtil.delFolder(Constant.datapath + "data/", false);
			System.out.println("文件存入DB线程数：" + threadnum);
			CreateIndexTask captureTask = new CreateIndexTask();
			captureTask.init(param, filecon);
			ThreadManager.getThreadManager().executeThread(captureTask);

			// 检查是否退出搜索的线程
			CheckThreadPoolTask checktask = new CheckThreadPoolTask();
			checktask.init(param, filecon);
			ThreadCheckThreadManager.getThreadManager().executeThread(checktask);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 取得filecon
	 * 
	 * @return FileContainer filecon 
	 */
	public static FileContainer getFilecon() {
		return filecon;
	}

	/**
	 * 设定filecon 
	 * 
	 * @param UpdateFileContainer filecon 
	 */
	public static void setFilecon(FileContainer filecon) {
		SearchFile.filecon = filecon;
	}
}
