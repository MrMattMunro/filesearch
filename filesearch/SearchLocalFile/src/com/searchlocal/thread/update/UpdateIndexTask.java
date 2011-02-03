/**
 * $RCSfile: UpdateIndexTask.java
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
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

import com.searchlocal.bean.ChangInfoBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.lucene.CurrentIndexUtil;
import com.searchlocal.param.FileParam;
import com.searchlocal.param.UpdateParam;
import com.searchlocal.service.FileService;
import com.searchlocal.thread.base.CRunnable;

/**
 * 更新索引并插入T_file
 * 
 * <p>Title: 更新索引并插入T_file</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class UpdateIndexTask extends CRunnable {

	/** 搜索参数 */
	private UpdateParam param;

	/** 文件容器 */
	private UpdateFileContainer filecon;

	/** 
	 * 初始化
	 * 
	 * @param param 搜索参数
	 * @param filecon 文件容器
	 */
	public void init(UpdateParam param, UpdateFileContainer filecon) {
		this.param = param;
		this.filecon = filecon;
	}

	/** 
	 * 设置过期
	 */
	public void setTimeOut() {
	}

	/** 
	 * 执行
	 */
	public void run() {
		updateIndex();
	}

	/** 
	 * 更新索引文件
	 */
	public boolean updateIndex() {

		// 需要删除的文档
		ConcurrentHashMap<String, Long> needDelfiles = filecon.getDelfile();
		// 需要添加的文档
		ConcurrentHashMap<String, Long> needAddfiles = filecon.getAndfile();
		// db名及搜索名
		String search = param.getSearchname();
		// 文件服务类
		FileService fileService = new FileService();
		// 处理需要删除的文档
		for (Iterator<String> iter = needDelfiles.keySet().iterator(); iter.hasNext();) {
			String path = (String)iter.next();
			CurrentIndexUtil.deleteDcoumentByPath(search, path);
			// 删除t_File记录
			try {
				fileService.deleteFileRecord(search, path);
			} catch (Exception e) {
			    e.printStackTrace();
			}
			// 从容器删除
			filecon.removeDelfile(path);
		}
		// 文件列表
		List<FileParam> filebeanList = new ArrayList<FileParam>();
		// 需要添加的文档
		for (Iterator<String> iter = needAddfiles.keySet().iterator(); iter.hasNext();) {
			String path = (String)iter.next();
			// 变化信息
			ChangInfoBean changeInfo = new ChangInfoBean();
			// 文件路径
			changeInfo.setPath(path);
			// 最后修改时间
			File file = new File(path);
			long lastModified = file.lastModified();
			if(file.exists()){
				changeInfo.setLastmodify(lastModified);
			}
			// 从容器删除
			filecon.removeAddfile(path);
			
			FileParam fileParam = new FileParam();
			//  文件路径
			fileParam.setPath(path);
			//  最后修改时间 
			fileParam.setLastModify(lastModified);
			// 是否存在错误
			fileParam.setError(Constant.NO_ERROR);
			try {
				CurrentIndexUtil.makeIndexByPath(search, changeInfo);
			} catch (LogicException e) {
				// 是否存在错误
				fileParam.setError(Constant.HAS_ERROR);
			}
			filebeanList.add(fileParam);
		}
		// 插入T_file记录
		try {
			// 生成csv文件
			fileService.createBatchFile(filebeanList, search);
			// 执行csv文件
			fileService.execBatch(search);
		} catch (DBException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} catch (LogicException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
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
}
