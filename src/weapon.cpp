////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "weapon.h"

//WEAPON
WeaponClass::WeaponClass()
{
    //set default values
    offsetSize.set(1,1,1);
    mat = NULL;
    fpMdl = NULL;

    //create muzzle flash
    fireMat = saiMaterial::load("fire");
    gunFire = saiObjModel::load("fire");
    gunFire->setMaterial(fireMat);
    gunFire->setPos(40*0.01,10*0.01,0);
    gunFire->setRot(0,-90,0);
    m_bFireVisible = false;
    m_nFireCounter = 0;
}

WeaponClass::~WeaponClass()
{
    if(mat != NULL)
        delete mat;
    if(fpMdl != NULL)
        delete fpMdl;
    delete fireMat;
    delete gunFire;
}

void WeaponClass::render(float fDeltaTime)
{
    //if no animation is currently played
    //play idle
    if(!fpMdl->isPlaying())
        fpMdl->playAnimation("idle",true);

    glPushMatrix();
    //set Identity Matrix
    //the weapon will always be rendered in front of the camera
    glLoadIdentity();
    //offset position
    glTranslatef(offsetPosition.x,offsetPosition.y,offsetPosition.z);
    glRotatef(offsetRotation.x,1,0,0);
    glRotatef(offsetRotation.y,0,1,0);
    glRotatef(offsetRotation.z,0,0,1);
    glScalef(offsetSize.x,offsetSize.y,offsetSize.z);

    //render muzzle flash if visible
    if(m_bFireVisible)
    {
        //muzzle flash is not affected by lights
        glDisable(GL_LIGHTING);
        gunFire->render();
        glEnable(GL_LIGHTING);
        m_nFireCounter++;
        if(m_nFireCounter > 10)
        {
            m_bFireVisible = false;
        }
    }
    fpMdl->render(fDeltaTime);
    glPopMatrix();
}

void WeaponClass::shoot()
{
    //shoot only if the shooting animation has finished
    if(fpMdl->hasStopedPlaying())
    {
        fpMdl->playAnimation("shoot",false);
        saiSoundManager::play("shot.wav");
        addAmmo(-1);
        m_bFireVisible = true;
        m_nFireCounter = 0;
    }
}

void WeaponClass::reload()
{
    //todo
    std::cout << "reload\n";
}

void WeaponClass::addAmmo(int amount)
{
    initAmmo += amount;
    if(initAmmo < 0)
        initAmmo = 0;
}

WeaponClass* WeaponClass::load(std::string fname)
{
    std::string filename = "../assets/weapons/" + fname + ".def";

    //load the textfile as a vector of string
    std::vector<std::string> lines = loadTextfile(filename);
    WeaponClass* newWeapon = new WeaponClass();
    for(unsigned int i=0;i<lines.size();i++) // loop through the lines
    {
        if(lines[i].c_str()[0] == 'n' && lines[i].c_str()[1] == 'm') //nm name
        {
            char nm[32];
            sscanf(lines[i].c_str(),"nm %s",nm);
            std::string nam(nm);
            newWeapon->Name = nam;
        }
        else if(lines[i].c_str()[0] == '1' && lines[i].c_str()[1] == 'p')//1p first person model
        {
            char nm[32];
            char mt[32];
            sscanf(lines[i].c_str(),"1p %s %s",nm,mt);
            std::string nam(nm);
            newWeapon->fpMdl = saiAnimatedmodel::load(nam);
            std::string mat(mt);
            newWeapon->mat = saiMaterial::load(mat);
            newWeapon->fpMdl->setMaterial(newWeapon->mat);
        }
        else if(lines[i].c_str()[0] == 'a' && lines[i].c_str()[1] == 'm')//am ammo
        {
            int ammo;
            int clip;
            int type;
            sscanf(lines[i].c_str(),"am %i %i %i",&ammo,&clip,&type);
            newWeapon->initAmmo = ammo;
            newWeapon->clipSize = clip;
            newWeapon->ammoType = type;
        }
        else if(lines[i].c_str()[0] == 'd' && lines[i].c_str()[1] == 'a')//da damage
        {
            int damage;
            int type;
            sscanf(lines[i].c_str(),"da %i %i",&damage,&type);
            newWeapon->damage = damage;
            newWeapon->type = type;
        }
        else if(lines[i].c_str()[0] == 'a' && lines[i].c_str()[1] == 'n')//an animation
        {
            char nm[32];
            int f1;
            int f2;
            int fr;
            sscanf(lines[i].c_str(),"an %s %i %i %i",nm,&f1,&f2,&fr);
            std::string nam(nm);
            newWeapon->fpMdl->addAnimation(f1,f2,fr,nam);
        }
        else if(lines[i].c_str()[0] == 'p' && lines[i].c_str()[1] == 's')//ps position
        {
            float px,py,pz;
            float rx,ry,rz;
            float sx,sy,sz;
            sscanf(lines[i].c_str(),"ps %f %f %f %f %f %f %f %f %f",&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
            newWeapon->offsetPosition.set(px*0.01,py*0.01,pz*0.01);
            newWeapon->offsetRotation.set(rx,ry,rz);
            newWeapon->offsetSize.set(sx,sy,sz);
        }
    }
    newWeapon->fpMdl->playAnimation("idle",true);
    return newWeapon;
}
