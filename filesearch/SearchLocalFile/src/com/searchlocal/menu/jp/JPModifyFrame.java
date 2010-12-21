package com.searchlocal.menu.jp;

import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;

import org.pushingpixels.substance.api.skin.SubstanceBusinessBlackSteelLookAndFeel;

import com.searchlocal.constants.Constant;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.exhander.ExceptionHandler;
import com.searchlocal.menu.CFrame;
import com.searchlocal.menu.CPanel;
import com.searchlocal.menu.MessageFrame;
import com.searchlocal.menu.SearchlocalApp;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.MessageParam;
import com.searchlocal.service.BaseService;
import com.searchlocal.thread.CheckThreadPoolTask;
import com.searchlocal.thread.SearchFile;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.XMLConfig;

public class JPModifyFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static JPModifyFrame c;

	private static CreateNewParam element;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	private static String indexpaxth = msg.getMsgbyId(Constant.label_indexdir);

	private static String msgsearch = msg.getMsgbyId(Constant.message_search);

	// checkbox
	JCheckBox excelcheckbox = new JCheckBox("excel");

	JCheckBox wordcheckbox = new JCheckBox("word");

	JCheckBox pdfcheckbox = new JCheckBox("pdf");

	JCheckBox pptcheckbox = new JCheckBox("ppt");

	JCheckBox chmcheckbox = new JCheckBox("chm");

	JCheckBox htmlcheckbox = new JCheckBox("html");

	JCheckBox txtcheckbox = new JCheckBox("txt");

	public JPModifyFrame(CreateNewParam param) {

		Container container = getContentPane();
		container.setLayout(null);
		setTitle(msg.getMsgbyId(Constant.title_modifysearch));

		if (null != param) {
			this.element = param;
		}
		CPanel panel = new CPanel();
		panel.setLayout(null);
		panel.setBounds(5, 5, 480, 274);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);
		
		panel.makeLabel(msg.getMsgbyId(Constant.label_searchname), 60, 10, 120, 25);
		panel.makeLabel(element.getSearchname(), 190, 10, 120, 25);

		panel.makeLabel(msg.getMsgbyId(Constant.label_searchdir), 60, 50, 120, 25);
		panel.makeLabel(element.getPath(), 190, 50, 120, 25);
		
		panel.makeLabel(msg.getMsgbyId(Constant.label_indexdir), 60, 90, 120, 25);
		panel.makeLabel(element.getIdexpath(), 190, 90, 120, 25);

		panel.makeLabel(msg.getMsgbyId(Constant.label_doc), 60, 130, 120, 25);
		excelcheckbox = panel.makeCheckbox("excel", 140, 130, 60, 20, "");
		wordcheckbox = panel.makeCheckbox("word", 200, 130, 60, 20, "");
		pdfcheckbox = panel.makeCheckbox("pdf", 260, 130, 50, 20, "");
	    pptcheckbox = panel.makeCheckbox("ppt", 310, 130, 50, 20, "");
	    htmlcheckbox = panel.makeCheckbox("html", 360, 130, 55, 20, "");
	    
	    txtcheckbox = panel.makeCheckbox("txt", 140, 150, 50, 20, "");
	    chmcheckbox = panel.makeCheckbox("chm", 190, 150, 60, 20, "");

		List selectList = this.element.getSelectfiletype();
		for (Object object : selectList) {
			String selecttype = (String) object;
			if (selecttype.equals("excel")) {
				excelcheckbox.setSelected(true);
				excelcheckbox.setEnabled(false);
			}

			if (selecttype.equals("word")) {
				wordcheckbox.setSelected(true);
				wordcheckbox.setEnabled(false);
			}

			if (selecttype.equals("pdf")) {
				pdfcheckbox.setSelected(true);
				pdfcheckbox.setEnabled(false);
			}

			if (selecttype.equals("ppt")) {
				pptcheckbox.setSelected(true);
				pptcheckbox.setEnabled(false);
			}

			if (selecttype.equals("html")) {
				htmlcheckbox.setSelected(true);
				htmlcheckbox.setEnabled(false);
			}

			if (selecttype.equals("txt")) {
				txtcheckbox.setSelected(true);
				txtcheckbox.setEnabled(false);
			}

			if (selecttype.equals("chm")) {
				chmcheckbox.setSelected(true);
				chmcheckbox.setEnabled(false);
			}
		}
		
		JButton confirmbutton = panel.makeButton(msg.getMsgbyId(Constant.button_confirm), 100, 190, 90, 20, "");
		confirmbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_UPDATINGINDEX);
				
				CreateNewParam param = new CreateNewParam();
				String indexpath = element.getIdexpath();
				List<String> selectfiletype = new ArrayList<String>();

				MessageParam indexpathparam = new MessageParam(indexpath, indexpaxth);
				
				List existedsearchTypeList = new ArrayList(element.getSelectfiletype());

				if (MessageFrame.checkNull(indexpathparam)) {
					if (excelcheckbox.isEnabled() && excelcheckbox.isSelected()) {
						selectfiletype.add("excel");
					}
					if (wordcheckbox.isEnabled() && wordcheckbox.isSelected()) {
						selectfiletype.add("word");
					}
					if (pdfcheckbox.isEnabled() && pdfcheckbox.isSelected()) {
						selectfiletype.add("pdf");
					}
					if (pptcheckbox.isEnabled() && pptcheckbox.isSelected()) {
						selectfiletype.add("ppt");
					}
					if (htmlcheckbox.isEnabled() && htmlcheckbox.isSelected()) {
						selectfiletype.add("html");
					}
					if (txtcheckbox.isEnabled() && txtcheckbox.isSelected()) {
						selectfiletype.add("txt");
					}
					if (chmcheckbox.isEnabled() && chmcheckbox.isSelected()) {
						selectfiletype.add("chm");
					}

					String searchname = element.getSearchname();

					param.setSearchname(searchname);
					param.setPath(element.getPath());

					param.setIdexpath(indexpath);
					param.setSelectfiletype(selectfiletype);

					SearchFile searchFile = new SearchFile();
					searchFile.listen(param);
					
					c.setVisible(false);
					
					while (true) {
						ThreadUtil.sleep(2000);
						if (CheckThreadPoolTask.isIsdone()) {
							String errormsg = msg.getMsgbyId(Constant.info_updatedindex);
							MessageFrame.showmessage(errormsg);
							// 更新XML搜索信息
							XMLConfig xmler = new XMLConfig();
							xmler.removeXML(param);
							// 加入新追加的搜索类型
							existedsearchTypeList.addAll(param.getSelectfiletype());
							param.setSelectfiletype(existedsearchTypeList);
							xmler.writeXML(param);
							
							SearchlocalApp.completeWork();
							String slfile = ConstantExeFileUtil.getOpenerbyId("slfile");
							CourseUtil.restart(slfile);
							break;
						}
					}
				}
			}
		});
		

		JButton deletebutton = panel.makeButton(msg.getMsgbyId(Constant.button_delete), 200, 190, 80, 20, "");
		
		deletebutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_DELETINGINDEX);
				String searchname = element.getSearchname();
				CreateNewParam param = new CreateNewParam();
				param.setSearchname(searchname);

				if (MessageFrame.confirmDeletAction(element.getIdexpath())) {
					// ɾ�?B
					BaseService baseService = new BaseService();
					try {
						baseService.dropDataBase(searchname);
					} catch (DBException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					} catch (LogicException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					}

					// ɾ�?��?ļ?
					FileUtil.delFolder(element.getIdexpath(), true);

					// ɾ�?ML��?
					XMLConfig xmler = new XMLConfig();
					xmler.removeXML(param);

					c.setVisible(false);
					String errormsg = msg.getMsgbyId(Constant.info_deletedindex);
					MessageFrame.showmessage(errormsg);
					
					SearchlocalApp.completeWork();
					String slfilepath = ConstantExeFileUtil.getOpenerbyId("slfile");
					CourseUtil.restart(slfilepath);
				}
			}
		});

		JButton cancelbutton = panel.makeButton(msg.getMsgbyId(Constant.button_cancel), 290, 190, 80, 20, "");
		cancelbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				c.setVisible(false);
			}
		});

        container.add(panel);
    	this.setSize(500, 284);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
	}

	public void showfame() throws UnsupportedLookAndFeelException,
			ClassNotFoundException, InstantiationException,
			IllegalAccessException {

		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				c = new JPModifyFrame(null);
				c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
				c.setVisible(true);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}

}