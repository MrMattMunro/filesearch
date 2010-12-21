package com.searchlocal.thread.concurrent;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

import com.searchlocal.bean.CurrentFileBean;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.FileParam;

/**
 * 文件容器
 * 
 * <p>Title: 保存DB文件，文件等等</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentFileContainer {

	/** DB存储的文件信息 */
	private  static ConcurrentHashMap<String, CurrentFileBean> dbfiles = new ConcurrentHashMap<String, CurrentFileBean>();

	/** 需要重建索引的文件信息 */
	private  static ConcurrentHashMap<String, CurrentFileBean> needindexfile = new ConcurrentHashMap<String, CurrentFileBean>();

	/** 所有建的索引 */
	private  static List<CreateNewParam> searchList = new ArrayList<CreateNewParam>();

	/** 整体可用 */
	private  static boolean abletostart = false;
	
	/** 完成同步 */
	private  static boolean isdone = false;

	/**
	 * @return Returns the canstart.
	 */
	public synchronized boolean getAbletostart() {
		return abletostart;
	}

	/**
	 * @param canstart
	 *            The canstart to set.
	 */
	public synchronized void setAbletoStart(boolean canstart) {
		this.abletostart = canstart;
		notifyAll();
	}

	/**
	 * @return Returns the dbfiles.
	 */
	public synchronized ConcurrentHashMap<String, CurrentFileBean> getDbfiles() {
		return dbfiles;
	}

	/**
	 * 放入DB文件
	 * 
	 * @param path 文件路径
	 * @return modify 文件修改时间
	 */
	public synchronized void putdbfile(String path, CurrentFileBean currentFileBean) {
		dbfiles.put(path, currentFileBean);
	}

	/**
	 * 清除DB文件
	 */
	public synchronized void cleardbfile() {
		dbfiles.clear();
		notifyAll();
	}

	/**
	 * 根据文件路径取得DB文件参数对象
	 * 
	 * @param key 文件路径
	 * @return FileParam 文件信息
	 */
	public synchronized FileParam getdbfile(String key) {
		FileParam param = new FileParam();
		while (dbfiles.size() == 0) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	    CurrentFileBean currentFileBean = (CurrentFileBean) dbfiles.get(key);
		Long lastmodify = currentFileBean.getLastmodify();
		param.setPath(key);
		param.setLastModify(lastmodify);
		notifyAll();
		return param;
	}

	/**
	 * @return Returns the searchList.
	 */
	public synchronized List<CreateNewParam> getSearchList() {
		return searchList;
	}

	/**
	 * @param searchList
	 *            The searchList to set.
	 */
	public synchronized void setSearchList(List<CreateNewParam> searchList) {
		this.searchList = searchList;
	}

	/**
	 * @return Returns the isdone.
	 */
	public synchronized boolean isIsdone() {
		return this.isdone;
	}

	/**
	 * @param isdone The isdone to set.
	 */
	public synchronized void setIsdone(boolean isdone) {
		this.isdone = isdone;
	}

	public synchronized ConcurrentHashMap<String, CurrentFileBean> getNeedindexfile() {
		return needindexfile;
	}

}
