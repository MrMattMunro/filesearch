package com.web.searchlocal.param;

import java.util.List;

public class CreateNewParam {

	private String id;

	private String path;

	private List selectfiletype;

	private String indexpath;

	/**
	 * @return Returns the idexpath.
	 */
	public String getIdexpath() {
		return indexpath;
	}

	/**
	 * @param idexpath
	 *            The idexpath to set.
	 */
	public void setIdexpath(String idexpath) {
		this.indexpath = idexpath;
	}

	/**
	 * @return Returns the selectfiletype.
	 */
	public List getSelectfiletype() {
		return selectfiletype;
	}

	/**
	 * @param selectfiletype
	 *            The selectfiletype to set.
	 */
	public void setSelectfiletype(List selectfiletype) {
		this.selectfiletype = selectfiletype;
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
	 * 取得id
	 * 
	 * @return String id 
	 */
	public String getId() {
		return id;
	}

	/**
	 * 设定id 
	 * 
	 * @param String id 
	 */
	public void setId(String id) {
		this.id = id;
	}

	/**
	 * 取得indexpath
	 * 
	 * @return String indexpath 
	 */
	public String getIndexpath() {
		return indexpath;
	}

	/**
	 * 设定indexpath 
	 * 
	 * @param String indexpath 
	 */
	public void setIndexpath(String indexpath) {
		this.indexpath = indexpath;
	}

}
