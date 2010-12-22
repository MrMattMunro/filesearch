package com.searchlocal.bean;

public class BaseFileBean {

	private String id;

	private String filename;

	private String path;

	private String lastmodify;

	private String content;
	

	/**
	 * @return Returns the content.
	 */
	public String getContent() {
		return content;
	}

	/**
	 * @param content
	 *            The content to set.
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
	 * @param filename
	 *            The filename to set.
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}

	/**
	 * @return Returns the lastmodify.
	 */
	public String getLastmodify() {
		return lastmodify;
	}

	/**
	 * @param lastmodify
	 *            The lastmodify to set.
	 */
	public void setLastmodify(String lastmodify) {
		this.lastmodify = lastmodify;
	}

	/**
	 * @return Returns the path.
	 */
	public String getPath() {
		return path;
	}

	/**
	 * @param path
	 *            The path to set.
	 */
	public void setPath(String path) {
		this.path = path;
	}

	/**
	 * @return Returns the id.
	 */
	public String getId() {
		return id;
	}

	/**
	 * @param id
	 *            The id to set.
	 */
	public void setId(String id) {
		this.id = id;
	}
}
