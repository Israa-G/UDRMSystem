#include "studentdialog.h"
#include "ui_studentdialog.h"

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::StudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add New Student");
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString StudentDialog::getName() const
{
    return ui->lineName->text().trimmed();
}

long long StudentDialog::getId() const
{
    return ui->lineId->text().toLongLong();
}

int StudentDialog::getYear() const
{
    return ui->spinYEar->value();
}

StudentDialog::~StudentDialog()
{
    delete ui;
}
