#ifndef _CREATIVE_BASE_UI_KERNEL_1589720896794_H
#define _CREATIVE_BASE_UI_KERNEL_1589720896794_H

#include <memory>
#include "basickernelexport.h"
#include "cxkernel/kernel/cxkernel.h"

#include "data/kernelenum.h"
#include "kernel/globalconst.h"
#include <QtWidgets/QUndoStack>

class GLQuickItem;
class KernelUI;
class CaptureModelN;

namespace qtuser_3d
{
	class CameraController;
	class ScreenCamera;
	class RenderCenter;
	class QuickScene3DWrapper;
}

namespace qtuser_core
{
	class UndoProxy;
	class JobExecutor;
	class CreativePluginCenter;
	class ApplicationConfiguration;
	class CXFileOpenAndSaveManager;
}

namespace cxkernel
{
	class EventTracking;
}

namespace creative_kernel
{
	class VisualScene;
	class ModelSpaceUndo;
	class ModelSpace;
	class ReuseableCache;
	class PrinterEntityUpdater;
	class ModelNSelector;
	class PrinterNetMng;
	class ThemeNotifier;
	class PrinterNotifier;
	class CommandCenter;
	class DumpProxy;
	class Translator;
	class CusModelListModel;
	class KernelPhase;
	class SliceFlow;
	class RClickMenuList;
	class ParameterManager;
	class UiParameterManager;
	class MaterialCenter;
	class SnapShot;
	class CADLoader;
	class PlatesDataManager;
	class PresetCenter;
	class PreferenceManager;
	class CX3DManager;
	class MessageNotify;
	class UnitTestFlow;
	class BASIC_KERNEL_API Kernel : public cxkernel::CXKernel
	{
		Q_OBJECT
		Q_PROPERTY(int currentPhase READ currentPhase NOTIFY currentPhaseChanged)
		Q_PROPERTY(bool isDefaultVisScene READ isDefaultVisScene NOTIFY visSceneChanged)

	public:
		Kernel(QObject* parent = nullptr);
		virtual ~Kernel();

		bool useFrameless() override { return true; }
		QString entryQmlFile() override;
		QStringList pluginFilter() override;
		void initializeContext() override;
		void initialize() override;
		void uninitialize() override;
		void loadUserSettings();

		int currentPhase();
		bool isDefaultVisScene();

		ReuseableCache* reuseableCache();
		qtuser_3d::RenderCenter* renderCenter();

		SliceFlow* sliceFlow();

		qtuser_3d::CameraController* cameraController();

		ModelSpace* modelSpace();
		CusModelListModel* listModel();
		ModelNSelector* modelSelector();

		VisualScene* visScene();

		ModelSpaceUndo* modelSpaceUndo();

		GlobalConst* globalConst();
		CommandCenter* commandCenter();
		cxkernel::EventTracking* sensorAnalytics();

		qtuser_core::ApplicationConfiguration* appConfiguration();
		ParameterManager* parameterManager();
		UiParameterManager* uiParameterManager();
		MaterialCenter* materialCenter();
		SnapShot* snapShot();
		MessageNotify* messageNotify();
		CX3DManager* cx3dManager();
		UnitTestFlow* unitTest();
		KernelUI* kernelUI();
		void setSceneClearColor(const QColor &color);

		Q_INVOKABLE void openFile();
		Q_INVOKABLE bool checkUnsavedChanges();
		Q_INVOKABLE void processCommandLine();
		Q_INVOKABLE bool blTestEnabled();
		//Q_INVOKABLE void setGLQuickItem(GLQuickItem* quickItem);
		Q_INVOKABLE void setScene3DWrapper(qtuser_3d::QuickScene3DWrapper* item);

		Q_INVOKABLE void setKernelPhase(int phase);   //invoke from qml
		void setKernelPhase(KernelPhaseType phase);   //invoke from c++, maybe not ui thread

		Q_INVOKABLE void captureSceneByZproject();
		Q_SIGNAL void scenceVerticalViewUpdated();
		Q_INVOKABLE bool addPrinter();

		Q_INVOKABLE bool isMaterialUsed(int materialIndex);
		Q_INVOKABLE void selectModelByMaterial(int materialIndex);
		Q_INVOKABLE void discardMaterial(int materialIndex);
		Q_INVOKABLE void changeMaterial(int materialIndex);

		Q_INVOKABLE void restartApplication();
		Q_INVOKABLE void restartApplication(bool keep_arguments);

        enum ClickType {
            NoModelMenu = 0,
            SingleModelMenu,
            MultiModelsMenu
        };
		void setRightClickType(ClickType type);
		bool canUndo();
	public slots:
		void viewChanged(bool requestUpdate);
		void onMachineChanged();
		void onModelMaterialUpdate();

	protected:
		void setKernelPhase(KernelPhase* phase);

	signals:
		void currentPhaseChanged();
		void visSceneChanged();

	protected:
		ReuseableCache* m_reusableCache;
		ModelSpace* m_modelSpace;
		CusModelListModel* m_modelListModel;
		PlatesDataManager* m_platesDataManager;

		qtuser_3d::RenderCenter* m_renderCenter;
		GlobalConst* m_globalConst;
		CommandCenter* m_commandCenter;
		SliceFlow* m_sliceFlow;
		CADLoader* m_cadLoader;

		qtuser_core::ApplicationConfiguration* m_configuration;

		qtuser_3d::CameraController* m_cameraController;

		VisualScene* m_visualScene;
		ModelNSelector* m_modelSelector;

		ModelSpaceUndo* m_modelSpaceUndo;

		KernelPhase* m_phases[3];
		KernelPhase* m_currentPhase;

		//internal
		ThemeNotifier* m_themeNotifier;
		PrinterNotifier* m_printerNotifier;

		DumpProxy* m_dumpProxy;

		cxkernel::EventTracking* m_sensorAnalytics;

		RClickMenuList* m_rclickMenuList;
		ParameterManager* m_parameterManager;
		std::unique_ptr<UiParameterManager> ui_parameter_manager_{ nullptr };

		SnapShot* m_snapShot;
		KernelUI* m_kernelUI;

		CaptureModelN *m_capture;
		PreferenceManager* m_preferenceMng;
		CX3DManager* m_cx3dManager;
		UnitTestFlow* m_unitTest;
		MessageNotify* m_message_notifier;
	};

	BASIC_KERNEL_API Kernel* getKernel();
	BASIC_KERNEL_API cxkernel::AppModule* createC3DContext();
}

#endif // _CREATIVE_BASE_UI_KERNEL_1589720896794_H
