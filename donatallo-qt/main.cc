/*
 * Copyright (C) 2016 Dmitry Marakasov
 *
 * This file is part of donatallo.
 *
 * donatallo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * donatallo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with donatallo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QHeaderView>

#include <libdonatallo/database.hh>

#include "model.hh"
#include "projectdelegate.hh"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	Donatallo::Database db;
	db.Load(DONATALLO_DATADIR "/database");

	Donatallo::Result res = db.GetAll().SortByName();

	Model model(db, res);

	QTreeView view;
	view.setRootIsDecorated(false);
	view.setModel(&model);

	view.header()->setSectionResizeMode(0, QHeaderView::Stretch);
	view.header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	view.header()->setStretchLastSection(false);

	ProjectDelegate delegate;

	db.ForEachDonationMethod([&](const Donatallo::DonationMethod& method) {
		delegate.addDonationMethod(
			QString::fromStdString(method.keyword),
			QString::fromStdString(method.name),
			QString::fromStdString(method.icon)
		);
	});

	view.setItemDelegate(&delegate);

	view.show();

	return app.exec();
}
