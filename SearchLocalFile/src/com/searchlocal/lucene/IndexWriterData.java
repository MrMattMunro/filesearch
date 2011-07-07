package com.searchlocal.lucene;

import org.apache.lucene.index.IndexWriter;

public class IndexWriterData {

	private int count;

	private IndexWriter writer;

	public IndexWriterData(IndexWriter writer, int count) {
		this.writer = writer;
		this.count = count;
	}

	/**
	 * @return Returns the count.
	 */
	public int getCount() {
		return count;
	}

	/**
	 * @param count The count to set.
	 */
	public void setCount(int count) {
		this.count = count;
	}

	/**
	 * @return Returns the writer.
	 */
	public IndexWriter getWriter() {
		return writer;
	}

	/**
	 * @param writer The writer to set.
	 */
	public void setWriter(IndexWriter writer) {
		this.writer = writer;
	}

}
