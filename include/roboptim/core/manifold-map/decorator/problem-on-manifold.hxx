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

#ifndef ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_PROBLEM_ON_MANIFOLD_HXX
#define ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_PROBLEM_ON_MANIFOLD_HXX

namespace roboptim
{
  template<class T>
  template<typename ... Types>
  ProblemOnManifold<T>::ProblemOnManifold(mnf::Manifold& manifold, Types& ... args)
    : T(args...),
      IsAProblemOnManifold(manifold)
  {
  }

  template<class T>
  ProblemOnManifold<T>::~ProblemOnManifold()
  {
  }

}
#endif //!ROBOPTIM_CORE_MANIFOLD_MAP_DECORATOR_PROBLEM_ON_MANIFOLD_HXX
