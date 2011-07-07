/*
 * Copyright(C) 2010 Slfile Company, Ltd. All Rights Reserved.
 */
package com.searchlocal.thread.concurrent;

import java.util.List;

import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;
import com.searchlocal.util.XMLConfig;

/**
 * 同步文件与数据库任务
 * 
 * <p>Title: 同步文件与数据库任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentFile {

	/**
	 * 同步方法
	 */
	public static void listen() {

		// 取得搜索信息
		XMLConfig xmlconfig = new XMLConfig();
		List<CreateNewParam> searches = xmlconfig.getEntityList();

		// 保证一个搜索对象有一个同步线程
		// directory作为零界资源，只能被一个对象获得，
		// 故一个directory只能有一个IndexWriter被打开
		// 开始同步DB和索引
		for (int i = 0; i < searches.size(); i++) {
			CreateNewParam createNewParam = searches.get(i);
			ConcurrentFileIndex.concurent(createNewParam);
		}
		// 重起搜索
		SearchlocalApp.completeWork();
		String slfilepath = ConstantExeFileUtil.getOpenerbyId("slfile");
		CourseUtil.restart(slfilepath);
	}
	
	public static void  main(String[] args){
		listen();
	}
}
