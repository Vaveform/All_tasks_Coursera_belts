#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

class FigureGeometry{
public:
	FigureGeometry(const Point& p, const Size& s) : p_({p.x, p.y}), s_({s.height, s.width}){};
	FigureGeometry() : p_({0, 0}), s_({0, 0}){};
	void SetPosition(Point new_position){
		p_.x = new_position.x;
		p_.y = new_position.y;
	}
	Point GetPosition() const{
		return p_;
	}
	void SetSize(Size new_size){
		s_.height = new_size.height;
		s_.width = new_size.width;
	}
	Size GetSize() const{
		return s_;
	}
private:
	Point p_;
	Size s_;
};


class Shape : public IShape{
public:
	  virtual void SetPosition(Point p) override final{
		  geometry.SetPosition(p);
	  }
	  virtual Point GetPosition() const override final{
		  return geometry.GetPosition();
	  }

	  virtual void SetSize(Size s) override final{
		  geometry.SetSize(s);
	  }
	  virtual Size GetSize() const override final{
		  return geometry.GetSize();
	  }

	  virtual void SetTexture(std::shared_ptr<ITexture> texture_) override final{
		  texture = texture_;
	  }
	  virtual ITexture* GetTexture() const override final{
		  return texture.get();
	  }
	  virtual shared_ptr<ITexture> GetSharedTexture() const {
		  return texture;
	  }
	  virtual std::unique_ptr<IShape> Clone() const override = 0;
	  virtual void Draw(Image&) const override {};
private:
	FigureGeometry geometry;
	shared_ptr<ITexture> texture;
};

class Rectangle : public Shape{
	virtual std::unique_ptr<IShape> Clone() const override{
		unique_ptr<IShape> cloned = make_unique<Rectangle>();
		cloned->SetPosition(this->GetPosition());
		cloned->SetSize(this->GetSize());
		cloned->SetTexture(this->GetSharedTexture());
		return cloned;
	}
	virtual void Draw(Image& image) const override{
		if(image.empty()){
			return;
		}
		Point position = this->GetPosition();
		Size size = this->GetSize();
		Size im_size = {0, 0};
		if(this->GetTexture() != nullptr){
			im_size = this->GetTexture()->GetSize();
		}
		for(int i = position.y; i < position.y + size.height; i++){
			for(int j = position.x; j < position.x + size.width; j++){
				if(i >= 0 && i < image.size() && j >= 0 && j < image[0].size()){
					if(j < position.x + im_size.width && i < position.y + im_size.height){
						const Image image_ref = this->GetTexture()->GetImage();
						image[i][j] = image_ref[i - position.y][j - position.x];
					}
					else{
						image[i][j] = '.';
					}
				}
			}
		}
	}
};


class Ellipse : public Shape{
	virtual std::unique_ptr<IShape> Clone() const override{
		unique_ptr<IShape> cloned = make_unique<Ellipse>();
		cloned->SetPosition(this->GetPosition());
		cloned->SetSize(this->GetSize());
		cloned->SetTexture(this->GetSharedTexture());
		return cloned;
	}
	virtual void Draw(Image& image) const override{
		if(image.empty()){
			return;
		}
		Point position = this->GetPosition();
		Size size = this->GetSize();
		Size im_size = {0, 0};
		if(this->GetTexture() != nullptr){
			im_size = this->GetTexture()->GetSize();
		}
		for(int i = position.y; i < position.y + size.height; i++){
			for(int j = position.x; j < position.x + size.width; j++){
				if(IsPointInEllipse({j - position.x, i - position.y},{size.width, size.height}) &&
						i < image.size() && i >= 0
						&& j < image[0].size() && j >= 0){
					if(j < position.x + im_size.width && i < position.y + im_size.height){
						const Image texture_ref = this->GetTexture()->GetImage();
						image[i][j] = texture_ref[i - position.y][j - position.x];
					}
					else{
						image[i][j] = '.';
					}
				}
			}
		}
	}
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	if(shape_type == ShapeType::Ellipse){
		return make_unique<Ellipse>();
	}
	return make_unique<Rectangle>();
}

