#pragma once

#include "objectsaver.hpp"


namespace events::handlers 
{
	template<class TBase>
	{
		virtual ~AbstractInnerHolder() {}

		virtual inline TBase& get() = 0;
		inline const TBase& get() const
		{
			return const_cast<AbstractInnerHolder<TBase>&>(*this).get();
		}
	};
	struct TInnerHolder : public AbstractInnerHolder<TBase>
	{
		using TInnerObject = typename ObjectSaver<TInner>::TObject;

		TInnerHolder(TInner _inner) :
			AbstractInnerHolder<TBase>(),
			inner(std::forward<TInner>(_inner))
		{ }

		virtual inline TBase& get() override
		{
			return static_cast<TBase&>(inner);
		}

		TInnerObject inner;
	};


	template<class TAssignBase, class TArgInner>
	AbstractInnerHolder<TAssignBase>& createInnerHolder(TArgInner&& inner)
	{
		using TAssignInner = decltype(inner);
		return *new TInnerHolder<TAssignBase, TAssignInner>(std::forward<TArgInner>(inner));
	}
}
