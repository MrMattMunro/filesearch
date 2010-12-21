package com.searchlocal.bean;

/**
 * 同步文件与数据库任务
 * 
 * <p>Title: 同步文件与数据库任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CurrentFileBean {
	
	// 最新修改时间
	private long lastmodify;
	
	// 是否做了同步处理
	private boolean hascurrent = false;

	public boolean isHascurrent() {
		return hascurrent;
	}
	
	public void setHascurrent(boolean hascurrent) {
		this.hascurrent = hascurrent;
	}

	public long getLastmodify() {
		return lastmodify;
	}

	public void setLastmodify(long lastmodify) {
		this.lastmodify = lastmodify;
	}
	
}
