// Copyright (C) 2015 by Félix Darricau, AIST, CNRS, EPITA
//                       Grégoire Duchemin, AIST, CNRS, EPITA
//
// This file is part of the roboptim.
//
// roboptim is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_DISPATCHER_HH
# define ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_DISPATCHER_HH

# include <manifolds/Manifold.h>
# include <manifolds/RealSpace.h>

namespace roboptim
{
  template <typename U> class DifferentiableFunctionOnManifold;

  /// \addtogroup roboptim_manifolds
  /// @{

  /// \brief Implements the differentiation between Sparse and Dense
  /// FunctionOnManifold.
  ///
  /// \tparam U input roboptim function type.
  /// \tparam T traits type of U. Either EigenMatrixDense or EigenMatrixSparse.
  template <typename U, typename T>
  struct Dispatcher
  {
    /// \brief gets the jacobian from the restricted problem
    ///
    /// \param instance the FunctionOnManifold
    /// \param jacobian the output jacobian
    static void unmapJacobian(const DifferentiableFunctionOnManifold<U>*,
			      typename U::jacobian_ref);

    /// \brief sets the jacobian on the manifold's tangent space with the
    /// computed value
    ///
    /// \param instance the FunctionOnManifold
    static void applyDiff(const DifferentiableFunctionOnManifold<U>*);
  };

  template <typename U>
  struct Dispatcher <U, roboptim::EigenMatrixDense>
  {
    static void unmapJacobian(const DifferentiableFunctionOnManifold<U>* instance,
			      typename U::jacobian_ref jacobian)
    {
      assert(jacobian.cols() == instance->inputSize());
      assert(jacobian.rows() == instance->outputSize());

      for (int i = 0; i < instance->mappingFromFunctionSize_; ++i)
	{
	  jacobian.col(static_cast<int>(instance->mappingFromFunction_[i])) = instance->mappedJacobian_.col(i);
	}
    }

    static void applyDiff(const DifferentiableFunctionOnManifold<U>* instance)
    {
      instance->manifold_->applyDiffRetractation(instance->tangentMappedJacobian, instance->mappedJacobian_, instance->mappedInput_);
    }
  };

  template <typename U>
  struct Dispatcher <U, roboptim::EigenMatrixSparse>
  {
    static void unmapJacobian(const DifferentiableFunctionOnManifold<U>* instance,
			      typename U::jacobian_ref jacobian)
    {
      assert(jacobian.cols() == instance->inputSize());
      assert(jacobian.rows() == instance->outputSize());

      for (int i = 0; i < instance->mappingFromFunctionSize_; ++i)
	{
	  jacobian.col(static_cast<int>(instance->mappingFromFunction_[i])) = instance->mappedJacobian_.col(i);
	}
    }

    static void applyDiff(const DifferentiableFunctionOnManifold<U>* instance)
    {
      if (instance->manifold_->getTypeId() != mnf::RealSpace(1).getTypeId())
        throw std::runtime_error("No Sparse support for non RealSpaces manifolds");
      else
        instance->tangentMappedJacobian = instance->mappedJacobian_;
    }
  };
} // end of namespace roboptim

#endif //! ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_DISPATCHER_HH
