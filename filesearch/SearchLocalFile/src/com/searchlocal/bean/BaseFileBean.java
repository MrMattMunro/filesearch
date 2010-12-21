package com.searchlocal.bean;

/**
 * 文件类基类
 * 
 * <p>Title: 文件类基类</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class BaseFileBean {
	
	/** 文件名 */
	private String filename;

	/** 文件路径 */
	private String path;

	/** 最后修改时间 */
	private long lastmodify;

	/** 内容 */
	private String content;

	/**
	 * @return Returns the content.
	 */
	public String getContent() {
		return content;
	}

	/**
	 * @param content The content to set.
	 */
	public void setContent(String content) {
		this.content = content;
	}

	/**
	 * @return Returns the filename.
	 */
	public String getFilename() {
		return filename;
	}

	/**
	 * @param filename The filename to set.
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}

	/**
	 * @return Returns the lastmodify.
	 */
	public long getLastmodify() {
		return lastmodify;
	}

	/**
	 * @param lastmodify The lastmodify to set.
	 */
	public void setLastmodify(long lastmodify) {
		this.lastmodify = lastmodify;
	}

	/**
	 * @return Returns the path.
	 */
	public String getPath() {
		return path;
	}

	/**
	 * @param path The path to set.
	 */
	public void setPath(String path) {
		this.path = path;
	}


}
