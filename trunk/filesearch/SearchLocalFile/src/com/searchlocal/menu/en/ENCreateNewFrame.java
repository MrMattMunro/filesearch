package com.searchlocal.menu.en;

import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;

import org.pushingpixels.substance.api.SubstanceLookAndFeel;
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
import com.searchlocal.service.ChmService;
import com.searchlocal.service.ExcelService;
import com.searchlocal.service.FileService;
import com.searchlocal.service.HtmlService;
import com.searchlocal.service.PdfService;
import com.searchlocal.service.PptService;
import com.searchlocal.service.TxtService;
import com.searchlocal.service.WordService;
import com.searchlocal.thread.CheckThreadPoolTask;
import com.searchlocal.thread.SearchFile;
import com.searchlocal.thread.util.ThreadUtil;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.XMLConfig;

public class ENCreateNewFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static ENCreateNewFrame c;

	// search name
	static JTextField searchnamefield;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public static String file_chooser_setsearchpath = msg
			.getMsgbyId(Constant.file_chooser_setsearchpath);

	public static String file_chooser_setindexpath = msg
			.getMsgbyId(Constant.file_chooser_setindexpath);

	public static String search_name = msg.getMsgbyId(Constant.label_searchname);

	public static String search_dir = msg.getMsgbyId(Constant.label_searchdir);

	public static String index_path = msg.getMsgbyId(Constant.label_indexdir);

	// select dir
	JFileChooser filechooser = new JFileChooser();

	JTextField selectdir = null;

	JTextField selectindexdir = null;

	// selectindex dir
	JFileChooser fileindexdirchooser = new JFileChooser();

	JButton selectindexdirbotton = new JButton(msg.getMsgbyId(Constant.button_select));

	// checkbox
	JCheckBox excelcheckbox = null;

	JCheckBox wordcheckbox = null;

	JCheckBox pdfcheckbox = null;

	JCheckBox pptcheckbox = null;

	JCheckBox htmlcheckbox = null;

	JCheckBox txtcheckbox = null;

	public ENCreateNewFrame() {
		Container container = getContentPane();
		container.setLayout(null);
		setTitle(msg.getMsgbyId(Constant.title_createnew));

		CPanel panel = new CPanel();
		panel.setLayout(null);
		// panel.setBounds(5, 5, 452, 274);
		panel.setBounds(5, 5, 480, 274);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);

		panel.makeLabel(msg.getMsgbyId(Constant.label_searchname), 60, 20, 130, 25);
		searchnamefield = panel.makeTextField(170, 20, 120, 20);
		searchnamefield.setEditable(true);

		panel.makeLabel(msg.getMsgbyId(Constant.label_searchdir), 60, 55, 120, 25);
		selectdir = panel.makeTextField(170, 55, 230, 20);
		selectdir.setEditable(false);
		JButton selectdirbotton = panel.makeButton(msg.getMsgbyId(Constant.button_select), 400, 55,
				55, 20, "");
		selectdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selectdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				filechooser.setDialogTitle(file_chooser_setsearchpath);
				filechooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				int state = filechooser.showOpenDialog(null);
				File file = filechooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					selectdir.setText(file.getAbsolutePath());
				}
			}
		});

		panel.makeLabel(msg.getMsgbyId(Constant.label_indexdir), 50, 90, 120, 25);
		selectindexdir = panel.makeTextField(170, 90, 230, 20);
		selectindexdir.setEditable(false);
		selectindexdirbotton = panel.makeButton(msg.getMsgbyId(Constant.button_select), 400, 90,
				55, 20, "");
		selectindexdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selectindexdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fileindexdirchooser.setDialogTitle(file_chooser_setindexpath);
				fileindexdirchooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				int state = fileindexdirchooser.showOpenDialog(null);
				File file = fileindexdirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					selectindexdir.setText(file.getAbsolutePath());
				}
			}
		});

		panel.makeLabel(msg.getMsgbyId(Constant.label_doc), 50, 125, 120, 25);

		excelcheckbox = panel.makeCheckbox("excel", 130, 125, 60, 20, "");
		wordcheckbox = panel.makeCheckbox("word", 185, 125, 60, 20, "");
		pdfcheckbox = panel.makeCheckbox("pdf", 240, 125, 50, 20, "");
		pptcheckbox = panel.makeCheckbox("ppt", 290, 125, 50, 20, "");
		htmlcheckbox = panel.makeCheckbox("html", 340, 125, 55, 20, "");
		txtcheckbox = panel.makeCheckbox("txt", 390, 125, 50, 20, "");

		JButton confirmbutton = panel.makeButton(msg.getMsgbyId(Constant.button_confirm), 150, 170,
				70, 20, "");
		confirmbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SearchlocalApp.startWork(Constant.ToolTipsClassify.TOOLTIPS_CREATINGINDEX);
				CreateNewParam param = new CreateNewParam();
				String searchname = searchnamefield.getText();
				String dir = selectdir.getText();
				String indexpath = selectindexdir.getText();
				List<String> selectfiletype = new ArrayList<String>();

				List<MessageParam> paramList = new ArrayList<MessageParam>();

				MessageParam mparam = new MessageParam(searchname, search_name);
				MessageParam dirparam = new MessageParam(dir, search_dir);
				MessageParam indexpathparam = new MessageParam(indexpath, index_path);

				paramList.add(mparam);
				paramList.add(dirparam);
				paramList.add(indexpathparam);

				XMLConfig xmler = new XMLConfig();

				List enetityList = xmler.getEntityList();

				if (MessageFrame.checkListNull(paramList)
						&& MessageFrame.checkSearcherList(paramList, enetityList)
						&& MessageFrame.checkIsCharatter(mparam)
						&& MessageFrame.checkIsallNums(mparam)) {
					if (excelcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.EXCEL);
					}
					if (wordcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.WORD);
					}
					if (pdfcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.PDF);
					}
					if (pptcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.PPT);
					}
					if (htmlcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.HTML);
					}
					if (txtcheckbox.isSelected()) {
						selectfiletype.add(Constant.FileNameClassify.TXT);
					}

					param.setSearchname(searchname);
					param.setPath(dir);
					param.setIdexpath(indexpath);
					param.setSelectfiletype(selectfiletype);

					BaseService baseService = new BaseService();
					WordService wordservice = new WordService();
					ExcelService excelService = new ExcelService();
					PdfService pdfService = new PdfService();
					PptService pptService = new PptService();
					ChmService chmService = new ChmService();
					HtmlService htmlService = new HtmlService();
					TxtService txtService = new TxtService();
					FileService fileService = new FileService();
					try {
						baseService.createDataBase(searchname);
						excelService.createExcelTable(searchname);
						wordservice.createWordTable(searchname);
						pdfService.createPdfTable(searchname);
						pptService.createPptTable(searchname);
						chmService.createChmTable(searchname);
						htmlService.createHtmlTable(searchname);
						txtService.createTxtTable(searchname);
						fileService.createFileTable(searchname);
					} catch (DBException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					} catch (LogicException e1) {
						String errmsg = ExceptionHandler.getMsg(e1);
						MessageFrame.showmessage(errmsg);
					}

					xmler.writeXML(param);
					SearchFile searchFile = new SearchFile();
					searchFile.listen(param);

					c.setVisible(false);
					while (true) {
						ThreadUtil.sleep(2000);
						if (CheckThreadPoolTask.isIsdone()) {
							String errormsg = msg.getMsgbyId(Constant.info_completeindex);
							MessageFrame.showmessage(errormsg);
							SearchlocalApp.completeWork();
							String slfile = ConstantExeFileUtil.getOpenerbyId("slfile");
							CourseUtil.restart(slfile);
							break;
						}
					}
				}
			}
		});

		JButton cancelbutton = panel.makeButton(msg.getMsgbyId(Constant.button_cancel), 230, 170,
				70, 20, "");
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

	public static void showframe() throws UnsupportedLookAndFeelException, ClassNotFoundException,
			InstantiationException, IllegalAccessException {
		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				c = new ENCreateNewFrame();
				c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
				c.setVisible(true);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {
	}
}
