#include "controlvariableswidget.h"
#include "ui_controlvariableswidget.h"

#include <QHeaderView>
#include <QEvent>

ControlVariablesWidget::ControlVariablesWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::ControlVariablesWidget)
{
    ui->setupUi(this);

    mToggleViewAction = new QAction(this);
    mToggleViewAction->setCheckable(true);
    mToggleViewAction->setText( windowTitle() );
    connect(mToggleViewAction, SIGNAL(triggered(bool)), SLOT(toggleView(bool)));

    enableButtons(false);
}

ControlVariablesWidget::~ControlVariablesWidget()
{
    delete ui;
}


void ControlVariablesWidget::setControlVariableList( const ControlVariableList& pControlVariableList )
{
    ui->controlVariableTable->setRowCount( pControlVariableList.size() );

    ControlVariable* controlVariable;
    unsigned int maxColSize = 100;

    for ( unsigned int i = 0; i < pControlVariableList.size(); ++i )
    {
        controlVariable = pControlVariableList[i];

        QTableWidgetItem* name = new QTableWidgetItem( QString::fromStdString(controlVariable->name()) );
        name->setFlags( Qt::ItemIsEnabled );
        ui->controlVariableTable->setItem(i, 0, name);

        // Value Table
        QTableWidget* valueTable = new QTableWidget(controlVariable->row(), controlVariable->col());
        valueTable->horizontalHeader()->setDefaultSectionSize(60);
        valueTable->horizontalHeader()->hide();
        valueTable->verticalHeader()->hide();
        connect(valueTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChanged(QTableWidgetItem*)) );

        for ( unsigned int row = 0; row < controlVariable->row(); ++row )
        {
            for ( unsigned int col = 0; col < controlVariable->col(); ++col )
            {
				QTableWidgetItem* item = new QTableWidgetItem( QString::number(controlVariable->heapElement(row, col) ) );
				item->setData( Qt::UserRole, i );
                valueTable->setItem( row, col, item );
            }
        }

        ui->controlVariableTable->setCellWidget(i, 1, valueTable );
        ui->controlVariableTable->verticalHeader()->resizeSection(i, controlVariable->row() * valueTable->verticalHeader()->defaultSectionSize() + 5 );

        maxColSize = qMax( maxColSize, controlVariable->col() * valueTable->horizontalHeader()->defaultSectionSize() );
    }

    // resize "Value" column
    ui->controlVariableTable->horizontalHeader()->resizeSection( 1, maxColSize + 5 );

    // Disable apply and cancel buttons
    enableButtons(false);
}

void ControlVariablesWidget::clear()
{
    ui->controlVariableTable->clearContents();
    ui->controlVariableTable->setRowCount(0);
}

void ControlVariablesWidget::on_apply_clicked()
{
    widgetToHeap();
    enableButtons(false);
}

void ControlVariablesWidget::on_cancel_clicked()
{
    heapToWidget();
    enableButtons(false);
}

void ControlVariablesWidget::itemChanged(QTableWidgetItem* pItem)
{
    bool ok;
    pItem->text().toDouble( &ok );
	// Gecersiz deger girilirse heap'te yer alan deger tekrar yazilir.
    if ( ok )
    {		
        enableButtons(true);
    }
    else
    {		
		int index = pItem->data( Qt::UserRole ).toInt();
		int row = pItem->row();
		int column = pItem->column();
		
		ControlVariable* controlVariable = DataRepository::instance()->controlVariables()[index];
		QTableWidget* tableWidget = (QTableWidget*)ui->controlVariableTable->cellWidget(index, 1);
		tableWidget->item( row, column )->setText( QString::number(controlVariable->heapElement(row, column)) );
    }
}

void ControlVariablesWidget::enableButtons(bool pEnable)
{
    ui->apply->setEnabled(pEnable);
    ui->cancel->setEnabled(pEnable);
}

void ControlVariablesWidget::heapToWidget()
{
    ControlVariable* controlVariable;
    ControlVariableList controlVariableList = DataRepository::instance()->controlVariables();
    for ( unsigned int i = 0; i < controlVariableList.size(); ++i )
    {
        QTableWidget* tableWidget = (QTableWidget*)ui->controlVariableTable->cellWidget(i, 1);
        controlVariable = controlVariableList[i];

        for ( unsigned int row = 0; row < controlVariable->row(); ++row )
        {
            for ( unsigned int col = 0; col < controlVariable->col(); ++col )
            {
                tableWidget->item(row, col)->setText( QString::number(controlVariable->heapElement(row, col)) );
            }
        }
    }
}

void ControlVariablesWidget::widgetToHeap()
{
    ControlVariable* controlVariable;
    ControlVariableList controlVariableList = DataRepository::instance()->controlVariables();
    for ( unsigned int i = 0; i < controlVariableList.size(); ++i )
    {
        QTableWidget* tableWidget = (QTableWidget*)ui->controlVariableTable->cellWidget(i, 1);
        controlVariable = controlVariableList[i];

        for ( unsigned int row = 0; row < controlVariable->row(); ++row )
        {
            for ( unsigned int col = 0; col < controlVariable->col(); ++col )
            {
                double val = tableWidget->item(row, col)->text().toDouble();
                controlVariable->setHeapElement(row, col, val);
            }
        }
    }
}

void ControlVariablesWidget::saveSettings( QSettings& pSettings )
{
    pSettings.beginGroup("controlVariablesWidget");
    pSettings.setValue("geometry", saveGeometry());
    pSettings.setValue("visible", isVisible());

	ControlVariable* controlVariable;
	ControlVariableList controlVariableList = DataRepository::instance()->controlVariables();
	for ( unsigned int i = 0; i < controlVariableList.size(); ++i )
	{
		controlVariable = controlVariableList[i];

		pSettings.beginGroup(ui->controlVariableTable->item(i, 0)->text());
		for ( unsigned int row = 0; row < controlVariable->row(); ++row )
		{
			for ( unsigned int col = 0; col < controlVariable->col(); ++col )
			{
				pSettings.setValue( QString("value[%1][%2]").arg(row).arg(col), controlVariable->heapElement(row, col));
			}
		}
		pSettings.endGroup();
	}
	pSettings.endGroup();
}

void ControlVariablesWidget::loadSettings(QSettings &pSettings)
{
    pSettings.beginGroup("controlVariablesWidget");
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    setVisible( pSettings.value("visible").toBool() );

	ControlVariable* controlVariable;
	ControlVariableList controlVariableList = DataRepository::instance()->controlVariables();
	for ( unsigned int i = 0; i < controlVariableList.size(); ++i )
	{
		QTableWidget* tableWidget = (QTableWidget*)ui->controlVariableTable->cellWidget(i, 1);
		controlVariable = controlVariableList[i];

		pSettings.beginGroup(ui->controlVariableTable->item(i, 0)->text());
		for ( unsigned int row = 0; row < controlVariable->row(); ++row )
		{
			for ( unsigned int col = 0; col < controlVariable->col(); ++col )
            {
                double defaultValue = controlVariable->heapElement(row, col);
                double val = pSettings.value( QString("value[%1][%2]").arg(row).arg(col), defaultValue ).toDouble();
				controlVariable->setHeapElement( row, col, val );
				tableWidget->item( row, col )->setText( QString::number(val) );
			}
		}
		pSettings.endGroup();
	}
    pSettings.endGroup();

	enableButtons(false);
}

QAction* ControlVariablesWidget::toggleViewAction() const
{
    return mToggleViewAction;
}

bool ControlVariablesWidget::event(QEvent *pEvent)
{
    switch (pEvent->type())
    {
    case QEvent::Hide:
        mToggleViewAction->setChecked(false);
        break;
    case QEvent::Show:
        mToggleViewAction->setChecked(true);
        break;
    default:
        break;
    }

    return QWidget::event(pEvent);
}

void ControlVariablesWidget::toggleView(bool pChecked)
{
    //if (b == q->isHidden())
    {
        if (pChecked)
            show();
        else
            close();
    }
}
