#include "logvariableswidget.h"
#include "ui_logvariableswidget.h"


LogVariablesWidget::LogVariablesWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::LogVariablesWidget)
{
    ui->setupUi(this);

    mToggleViewAction = new QAction(this);
    mToggleViewAction->setCheckable(true);
    mToggleViewAction->setText( windowTitle() );
    connect(mToggleViewAction, SIGNAL(triggered(bool)), SLOT(toggleView(bool)));

	mHeaderView = new CheckedHeader(Qt::Vertical, ui->logVariableTable);
	connect( mHeaderView, SIGNAL(toggled(int,bool)), SLOT(setLogVariableChecked(int, bool)) );
    ui->logVariableTable->setVerticalHeader( mHeaderView );
}

LogVariablesWidget::~LogVariablesWidget()
{
    delete ui;
}

void LogVariablesWidget::setLogVariableList(const LogVariableList &pLogVariableList)
{
    ui->logVariableTable->setRowCount( pLogVariableList.size() );

    LogVariable* logVariable;
    for ( size_t i = 0; i < pLogVariableList.size(); ++i )
    {
        logVariable = pLogVariableList[i];

        ui->logVariableTable->setItem( i, 0, new QTableWidgetItem(QString::fromStdString(logVariable->name())) );
		ui->logVariableTable->setItem(i, 1, new QTableWidgetItem());
        ui->logVariableTable->setItem(i, 2, new QTableWidgetItem());
        ui->logVariableTable->setItem(i, 3, new QTableWidgetItem());
		setLogVariableChecked( i, false );
    }
}

void LogVariablesWidget::clear()
{
    ui->logVariableTable->setRowCount(0);
}

void LogVariablesWidget::mainFrequencyChanged(double pFrequency)
{
	// change frequency of unchecked log variables
	for ( int i = 0; i < ui->logVariableTable->rowCount(); ++i )
	{
		if ( !mHeaderView->isChecked(i) )
		{
			setFrequency(i, pFrequency);
		}
	}
}

void LogVariablesWidget::mainDurationChanged( double pDuration )
{
	// change duration of unchecked log variables
	for ( int i = 0; i < ui->logVariableTable->rowCount(); ++i )
	{
		if ( !mHeaderView->isChecked(i) )
		{
			setDuration( i, pDuration );
		}
	}
}

void LogVariablesWidget::saveSettings(QSettings &pSettings)
{
    pSettings.beginGroup("logVariablesWidget");
    pSettings.setValue("geometry", saveGeometry());
    pSettings.setValue("visible", isVisible());

    for ( int i = 0; i < ui->logVariableTable->rowCount(); ++i )
    {
		if ( mHeaderView->isChecked(i) )
		{
			pSettings.beginGroup(ui->logVariableTable->item(i, 0)->text());
			pSettings.setValue("frequency", ui->logVariableTable->item(i, 1)->text());
			pSettings.setValue("startTime", ui->logVariableTable->item(i, 2)->text());
			pSettings.setValue("duration", ui->logVariableTable->item(i, 3)->text());
			pSettings.endGroup();
		}
    }
    pSettings.endGroup();
}

void LogVariablesWidget::loadSettings(QSettings &pSettings)
{
    pSettings.beginGroup("logVariablesWidget");
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    setVisible( pSettings.value("visible").toBool() );

    for ( int i = 0; i < ui->logVariableTable->rowCount(); ++i )
    {
        if ( pSettings.childGroups().contains(ui->logVariableTable->item(i, 0)->text()) )
        {
            pSettings.beginGroup(ui->logVariableTable->item(i, 0)->text());
			setLogVariableChecked( i, true );
			setFrequency(i, pSettings.value("frequency", DataRepository::instance()->frequency()).toDouble());
			setStartTime(i, pSettings.value("startTime", 0).toDouble());
			setDuration(i, pSettings.value("duration", DataRepository::instance()->duration()).toDouble());
            pSettings.endGroup();
        }
    }

    pSettings.endGroup();
}

void LogVariablesWidget::on_logVariableTable_itemChanged(QTableWidgetItem *item)
{
	if ( item->column() == 1 )      // Frequency
	{
		setFrequency(item->row(), item->text().toDouble());
	}
	else if ( item->column() == 2 ) // Start Time
	{
		setStartTime(item->row(), item->text().toDouble());
	}
	else if ( item->column() == 3 ) // Duration
	{
        setDuration(item->row(), item->text().toDouble());
    }
}

void LogVariablesWidget::setFrequency( int pIndex, double pFrequency )
{
	LogVariable* logVariable = DataRepository::instance()->logVariables()[pIndex];
	QTableWidgetItem* frequency = ui->logVariableTable->item(pIndex, 1);
	if ( pFrequency > 0 )
	{
		logVariable->setFrequency( pFrequency );
		frequency->setText( QString::number(pFrequency) );
	}
	else
	{
		frequency->setText( QString::number(logVariable->frequency()) );
	}
}

void LogVariablesWidget::setStartTime( int pIndex, double pStartTime )
{
	LogVariable* logVariable = DataRepository::instance()->logVariables()[pIndex];
	QTableWidgetItem* startTime = ui->logVariableTable->item(pIndex, 2);
	if ( pStartTime >= 0 )
	{
		logVariable->setStartTime( pStartTime );
		startTime->setText( QString::number(pStartTime) );
	}
	else
	{
		startTime->setText( QString::number(logVariable->startTime()) );
	}
}

void LogVariablesWidget::setDuration( int pIndex, double pDuration )
{
	LogVariable* logVariable = DataRepository::instance()->logVariables()[pIndex];
	QTableWidgetItem* duration = ui->logVariableTable->item(pIndex, 3);
	if ( pDuration > 0 )
	{
		logVariable->setDuration( pDuration );
		duration->setText( QString::number(pDuration) );
	}
	else
	{
		duration->setText( QString::number(logVariable->duration()) );
	}
}

void LogVariablesWidget::setLogVariableChecked( int pIndex, bool pChecked )
{
	mHeaderView->setChecked(pIndex, pChecked);	
	if ( pChecked )
	{
		Qt::ItemFlags flags = Qt::ItemIsEditable|Qt::ItemIsSelectable
			|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled;

		ui->logVariableTable->item(pIndex, 0)->setFlags(Qt::ItemIsEnabled);
		ui->logVariableTable->item(pIndex, 1)->setFlags(flags);		
		ui->logVariableTable->item(pIndex, 2)->setFlags(flags);		
		ui->logVariableTable->item(pIndex, 3)->setFlags(flags);		
	}
	else
	{
		ui->logVariableTable->item(pIndex, 0)->setFlags(Qt::NoItemFlags);
		ui->logVariableTable->item(pIndex, 1)->setFlags(Qt::NoItemFlags);
		ui->logVariableTable->item(pIndex, 2)->setFlags(Qt::NoItemFlags);
		ui->logVariableTable->item(pIndex, 3)->setFlags(Qt::NoItemFlags);

		setFrequency(pIndex, DataRepository::instance()->frequency());
		setStartTime(pIndex, 0);
		setDuration(pIndex, DataRepository::instance()->duration());
	}

	QFont font = ui->logVariableTable->item(pIndex, 0)->font();
	font.setBold(pChecked);
	ui->logVariableTable->item(pIndex, 0)->setFont(font);
	ui->logVariableTable->item(pIndex, 1)->setFont(font);
	ui->logVariableTable->item(pIndex, 2)->setFont(font);
	ui->logVariableTable->item(pIndex, 3)->setFont(font);
}

QAction* LogVariablesWidget::toggleViewAction() const
{
    return mToggleViewAction;
}

bool LogVariablesWidget::event(QEvent *pEvent)
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

void LogVariablesWidget::toggleView(bool pChecked)
{
    //if (b == q->isHidden())
    {
        if (pChecked)
            show();
        else
            close();
    }
}
