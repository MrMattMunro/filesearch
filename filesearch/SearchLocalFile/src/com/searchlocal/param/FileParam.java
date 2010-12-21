package com.searchlocal.param;

public class FileParam {

	private String path;

	Long lastModify;

	String error;

	/**
	 * @return Returns the lastModify.
	 */
	public Long getLastModify() {
		return lastModify;
	}

	/**
	 * @param lastModify
	 *            The lastModify to set.
	 */
	public void setLastModify(Long lastModify) {
		this.lastModify = lastModify;
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

	public FileParam() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @return Returns the error.
	 */
	public String getError() {
		return error;
	}

	/**
	 * @param error The error to set.
	 */
	public void setError(String error) {
		this.error = error;
	}

}
