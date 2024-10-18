#ifndef FINISHABLE_H_
# define FINISHABLE_H_

// 終了可能なものすべての基底クラスとする
class Finishable {
	public:
		Finishable(void);
		virtual ~Finishable();
		virtual bool is_finished() const = 0;
};

#endif