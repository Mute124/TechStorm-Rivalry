<?xml version="1.0" encoding="utf-8"?>
<file>
	<mod_name>Example mod</mod_name>
	<afflictions>
		<affliction>
			<name>Example Name</name>
			<tooltip>This is how you add afflictions!</tooltip>
			<description></description>
			<icon></icon>
			<!--0 = bad 1 = mixed 2 = good-->
			<implication></implication>
			<severity></severity>
			<causes>
				<!--Put the damage type tag that can cause this here!-->
				<cause></cause>
			</causes>
			<!--What can treat this affliction?-->
			<treatments>
				<!--What heals the player of this affliction? ONLY PUT THE NAME!!-->
				<treatment></treatment>
			</treatments>
			<!--What does this affliction do?-->
			<affects>
				<affect>
					<!--What about the player gets affected?-->
					<targetcomponent></targetcomponent>
					<!--how much should be changed each affliction update?-->
					<changefactor></changefactor>
				</affect>
			</affects>
		</affliction>
	</afflictions>
</file>