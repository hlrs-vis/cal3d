//****************************************************************************//
// coreskeleton.cpp                                                           //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/error.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/corebone.h"

 /*****************************************************************************/
/** Constructs the core skeleton instance.
  *
  * This function is the default constructor of the core skeleton instance.
  *****************************************************************************/

CalCoreSkeleton::CalCoreSkeleton()
{
}

 /*****************************************************************************/
/** Destructs the core skeleton instance.
  *
  * This function is the destructor of the core skeleton instance.
  *****************************************************************************/

CalCoreSkeleton::~CalCoreSkeleton()
{
  assert(m_listRootCoreBoneId.empty());
  assert(m_vectorCoreBone.empty());
}

 /*****************************************************************************/
/** Adds a core bone.
  *
  * This function adds a core bone to the core skeleton instance.
  *
  * @param pCoreBone A pointer to the core bone that should be added.
  *
  * @return One of the following values:
  *         \li the assigned bone \b ID of the added core bone
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreSkeleton::addCoreBone(CalCoreBone *pCoreBone)
{
  // get next bone id
  int boneId;
  boneId = m_vectorCoreBone.size();

  m_vectorCoreBone.push_back(pCoreBone);

  // if necessary, add the core bone to the root bone list
  if(pCoreBone->getParentId() == -1)
  {
    m_listRootCoreBoneId.push_back(boneId);
  }

  // add a reference from the bone's name to its id
  mapCoreBoneName( boneId, pCoreBone->getName() );

  return boneId;
}

 /*****************************************************************************/
/** Calculates the current state.
  *
  * This function calculates the current state of the core skeleton instance by
  * calculating all the core bone states.
  *****************************************************************************/

void CalCoreSkeleton::calculateState()
{
  // calculate all bone states of the skeleton
  std::list<int>::iterator iteratorRootCoreBoneId;
  for(iteratorRootCoreBoneId = m_listRootCoreBoneId.begin(); iteratorRootCoreBoneId != m_listRootCoreBoneId.end(); ++iteratorRootCoreBoneId)
  {
    m_vectorCoreBone[*iteratorRootCoreBoneId]->calculateState();
  }
}

 /*****************************************************************************/
/** Creates the core skeleton instance.
  *
  * This function creates the core skeleton instance.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreSkeleton::create()
{
  return true;
}

 /*****************************************************************************/
/** Destroys the core skeleton instance.
  *
  * This function destroys all data stored in the core skeleton instance and
  * frees all allocated memory.
  *****************************************************************************/

void CalCoreSkeleton::destroy()
{
  // destroy all core animations
  std::vector<CalCoreBone *>::iterator iteratorCoreBone;
  for(iteratorCoreBone = m_vectorCoreBone.begin(); iteratorCoreBone != m_vectorCoreBone.end(); ++iteratorCoreBone)
  {
    (*iteratorCoreBone)->destroy();
    delete (*iteratorCoreBone);
  }

  m_vectorCoreBone.clear();

  // clear the bone name mapping
  m_mapCoreBoneNames.clear();

  // clear root bone id list
  m_listRootCoreBoneId.clear();
}

 /*****************************************************************************/
/** Provides access to a core bone.
  *
  * This function returns the core bone with the given ID.
  *
  * @param coreBoneId The ID of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core bone
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreBone *CalCoreSkeleton::getCoreBone(int coreBoneId)
{
  if((coreBoneId < 0) || (coreBoneId >= (int)m_vectorCoreBone.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreBone[coreBoneId];
}

 /*****************************************************************************/
/** Provides access to a core bone.
  *
  * This function returns the core bone with the given name.
  *
  * @param strName The name of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core bone
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreBone* CalCoreSkeleton::getCoreBone(const std::string& strName)
{
   return getCoreBone( getCoreBoneId( strName ));
}

 /*****************************************************************************/
/** Returns the ID of a specified core bone.
  *
  * This function returns the ID of a specified core bone.
  *
  * @param strName The name of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li the \b ID of the core bone
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreSkeleton::getCoreBoneId(const std::string& strName)
{
  //Check to make sure the mapping exists
  if (m_mapCoreBoneNames.count(strName) <= 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  return m_mapCoreBoneNames[strName];

}

 /*****************************************************************************/
/** Maps the name of a bone to a specific bone id
  *
  * This function returns true or false depending on whether the mapping
  * was successful or not. Note that it is possible to overwrite and existing
  * mapping and no error will be given.
  *
  * @param coreBoneId The id of the core bone to be associated with the name.
  * @param strName The name of the core bone that will be associated with the id.
  *
  * @return One of the following values:
  *         \li true if the mapping was successful
  *         \li false if an invalid ID was given
  *****************************************************************************/

bool CalCoreSkeleton::mapCoreBoneName(int coreBoneId, const std::string& strName)
{
   //Make sure the ID given is a valid corebone ID number
   if ((coreBoneId < 0) || (coreBoneId >= (int)m_vectorCoreBone.size()))
   {
      return false;
   }

   //Add the mapping or overwrite an existing mapping
   m_mapCoreBoneNames[strName] = coreBoneId;

   return true;
}

 /*****************************************************************************/
/** Returns the root core bone id list.
  *
  * This function returns the list that contains all root core bone IDs of the
  * core skeleton instance.
  *
  * @return A reference to the root core bone id list.
  *****************************************************************************/

std::list<int>& CalCoreSkeleton::getListRootCoreBoneId()
{
  return m_listRootCoreBoneId;
}

 /*****************************************************************************/
/** Returns the core bone vector.
  *
  * This function returns the vector that contains all core bones of the core
  * skeleton instance.
  *
  * @return A reference to the core bone vector.
  *****************************************************************************/

std::vector<CalCoreBone *>& CalCoreSkeleton::getVectorCoreBone()
{
  return m_vectorCoreBone;
}

void CalCoreSkeleton::calculateBoundingBox(CalCoreModel * pCoreModel)
{
   for(size_t boneId=0;boneId<m_vectorCoreBone.size();++boneId)
   {
      m_vectorCoreBone[boneId]->calculateBoundingBox(pCoreModel);
   }

}


//****************************************************************************//
