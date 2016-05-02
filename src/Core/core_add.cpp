#include "core.h" 

void Core::addObject(const Array<double> &parametrs, Primitive_Type type) {
	GraphPrimitive* newobj;
	switch (type) {
	case IsPoint: if (parametrs.size() == 2)
		newobj = new Point(parametrs[0], parametrs[1]);
	case IsSegment: if (parametrs.size() == 4) {
		Point *t1 = new Point(parametrs[0], parametrs[1]);
		Point *t2 = new Point(parametrs[2], parametrs[3]);
		newobj = new Segment(t1, t2);
	}
	case IsCircle: if (parametrs.size() == 3) {
		Point *t1 = new Point(parametrs[0], parametrs[1]);
		newobj = new Circle(t1, parametrs[2]);
	}
	}
	objects.push_back(newobj);
	return;
}


bool Core::addRestriction(List<unsigned>* id, double* parametr, RestrictType type) {
	List<GraphPrimitive*> id_obj;
	BasicRestriction* newrest = 0;
	List<GraphPrimitive*>::Marker mar1(objects);
	for (size_t i = 0; i < objects.sizeList();i++) {
		List<unsigned>::Marker mar_id(*id);
		for (size_t j = 0;j < id->sizeList();j++) {
			if (mar1.get_current()->showId() == mar_id.get_current())
				id_obj.push_back(mar1.get_current());
			mar_id.move_next();
		}
		mar1.move_next();
	}

	Array<double*> params;
	List<GraphPrimitive*>::Marker mar(id_obj);
	switch (type) {

	case RT_FIX:
		for (size_t i = 0;i < id_obj.sizeList();i++) {
			mar.get_current()->fix(1);
			mar.move_next();
		}
		restrictions.push_back(newrest);
		return true;
		break;

	case RT_P2PDIST:
		if (id_obj.sizeList() == 2) {
			Point *p1 = dynamic_cast<Point*> (mar.get_current());
			mar.move_next();
			Point *p2 = dynamic_cast<Point*> (mar.get_current());
			newrest = new RestrP2PDIST(p1, p2, parametr);
			if (!p1->isFixed() && !p2->isFixed()) {
				params.push_back(p1->x());
				params.push_back(p1->y());
				params.push_back(p2->x());
				params.push_back(p2->y());
			}
		}
		break;

	case RT_P2SDIST:
		if (id_obj.sizeList() == 3) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Point *p1 = dynamic_cast<Point*> (mar.get_current());
			mar.move_next();
			Point *p2 = dynamic_cast<Point*> (mar.get_current());
			mar.move_next();
			Point *p3 = dynamic_cast<Point*> (mar.get_current());
			newrest = new RestrP2SDIST(p1, p2, p3, parametr);
			if (!p1->isFixed() && !p2->isFixed() && !p3->isFixed()) {
				params.push_back(p1->x());
				params.push_back(p1->y());
				params.push_back(p2->x());
				params.push_back(p2->y());
				params.push_back(p3->x());
				params.push_back(p3->y());
			}
		}
		break;

	case RT_P2SDISTEX:
		if (id_obj.sizeList() == 3) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Point *p1 = dynamic_cast<Point*> (mar.get_current());
			mar.move_next();
			Point *p2 = dynamic_cast<Point*> (mar.get_current());
			mar.move_next();
			Point *p3 = dynamic_cast<Point*> (mar.get_current());
			newrest = new RestrP2SDISTEX(p1, p2, p3, parametr);
			if (!p1->isFixed() && !p2->isFixed() && !p3->isFixed()) {
				params.push_back(p1->x());
				params.push_back(p1->y());
				params.push_back(p2->x());
				params.push_back(p2->y());
				params.push_back(p3->x());
				params.push_back(p3->y());
			}
		}
		break;

	case RT_S2SANGLE:
		if (id_obj.sizeList() == 2) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Segment *p1 = dynamic_cast<Segment*> (mar.get_current());
			mar.move_next();
			Segment *p2 = dynamic_cast<Segment*> (mar.get_current());
			newrest = new RestrS2SANGLE(p1, p2, parametr);
			if (!p1->isFixed() && !p2->isFixed()) {
				params.push_back(p1->getP1()->x());
				params.push_back(p1->getP1()->y());
				params.push_back(p1->getP2()->x());
				params.push_back(p1->getP2()->y());
				params.push_back(p2->getP1()->x());
				params.push_back(p2->getP1()->y());
				params.push_back(p2->getP2()->x());
				params.push_back(p2->getP2()->y());
			}
		}
		break;

	case RT_S2SEQUALS:
		if (id_obj.sizeList() == 2) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Segment *p1 = dynamic_cast<Segment*> (mar.get_current());
			mar.move_next();
			Segment *p2 = dynamic_cast<Segment*> (mar.get_current());
			newrest = new RestrS2SEQUALS(p1, p2);
			if (!p1->isFixed() && !p2->isFixed()) {
				params.push_back(p1->getP1()->x());
				params.push_back(p1->getP1()->y());
				params.push_back(p1->getP2()->x());
				params.push_back(p1->getP2()->y());
				params.push_back(p2->getP1()->x());
				params.push_back(p2->getP1()->y());
				params.push_back(p2->getP2()->x());
				params.push_back(p2->getP2()->y());
			}
		}
		break;

	case RT_S2SPARAL:
		if (id_obj.sizeList() == 2) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Segment *p1 = dynamic_cast<Segment*> (mar.get_current());
			mar.move_next();
			Segment *p2 = dynamic_cast<Segment*> (mar.get_current());
			newrest = new RestrS2SPARAL(p1, p2);
			if (!p1->isFixed() && !p2->isFixed()) {
				params.push_back(p1->getP1()->x());
				params.push_back(p1->getP1()->y());
				params.push_back(p1->getP2()->x());
				params.push_back(p1->getP2()->y());
				params.push_back(p2->getP1()->x());
				params.push_back(p2->getP1()->y());
				params.push_back(p2->getP2()->x());
				params.push_back(p2->getP2()->y());
			}
		}
		break;

	case RT_S2SORTHO:
		if (id_obj.sizeList() == 2) {
			List<GraphPrimitive*>::Marker mar(id_obj);
			Segment *p1 = dynamic_cast<Segment*> (mar.get_current());
			mar.move_next();
			Segment *p2 = dynamic_cast<Segment*> (mar.get_current());
			newrest = new RestrS2SORTHO(p1, p2);
			if (!p1->isFixed() && !p2->isFixed()) {
				params.push_back(p1->getP1()->x());
				params.push_back(p1->getP1()->y());
				params.push_back(p1->getP2()->x());
				params.push_back(p1->getP2()->y());
				params.push_back(p2->getP1()->x());
				params.push_back(p2->getP1()->y());
				params.push_back(p2->getP2()->x());
				params.push_back(p2->getP2()->y());
			}
		}
		break;
	}
	
	
	if (!params.size()) return false;
	CHJSolver solv;
	MyFunction f1(params);
	f1.addRestr(newrest);
	if (solv.solve(&f1, params)) {
		restrictions.push_back(newrest);
		return true;
	}
	return false;
}

